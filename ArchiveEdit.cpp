/*******************************************************************************************
**
** Project: Patch Generator
** File: ArchiveEdit.cpp
**
** Copyright (C) 2012 techvoid.
** All rights reserved.
** http://sourceforge.net/projects/patchgenerator/
**
** This program is free software: you can redistribute it and/or modify it under the terms
** of the GNU General Public License as published by the Free Software Foundation, either
** version 3 of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
** without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License along with this
** program. If not, see <http://www.gnu.org/licenses/>.
**
*******************************************************************************************/

/*======================================== HEADERS =======================================*/

#include "ArchiveEdit.h"

#include <QtGui/QProgressDialog>
#include <QtGui/QMessageBox>

#include <QtCore/QBuffer>
#include <QtCore/QTextStream>
#include <QtCore/QFileInfo>
#include <QtCore/QDirIterator>
#include <QtCore/QDebug>

#define QUAZIP_STATIC

#include <quazip.h>
#include <quazipfile.h>
#include <QuaZipFileInfo.h>

/*======================================== PUBLIC ========================================*/

ArchiveEdit::ArchiveEdit(QWidget *pParent) :
    QObject(pParent),
    rParentWidget(pParent)
{
}

bool ArchiveEdit::Repackage(const QString &pFrom, const QString &pTo,
                            const QString &pSaveAs)
{
    if (pFrom.isEmpty() || pTo.isEmpty() || pSaveAs.isEmpty())
        return false;

    bool isFromDir = QFileInfo(pFrom).isDir();
    bool isToDir = QFileInfo(pTo).isDir();

    QProgressDialog mProgress(rParentWidget);
    mProgress.setCancelButtonText("Abort");
    mProgress.setWindowFlags(rParentWidget->windowFlags());
    mProgress.setMinimumSize(mProgress.size());
    mProgress.setMaximumSize(mProgress.size());
    mProgress.setWindowModality(Qt::WindowModal);
    mProgress.setMinimumDuration(0);
    mProgress.setLabelText("Calculating...");

    QuaZip mArchiveFrom;
    QList<QuaZipFileInfo64> tArchiveFromList;

    if (isFromDir) {
        QDirIterator iterator(pFrom, QDir::Files | QDir::NoDotAndDotDot,
                              QDirIterator::Subdirectories);
        while (iterator.hasNext()) {
            if (mProgress.wasCanceled())
                return false;

            iterator.next();
            tArchiveFromList.append(ToZipFileInfo(iterator));
        }
    } else {
        mArchiveFrom.setZipName(pFrom);
        if (!mArchiveFrom.open(QuaZip::mdUnzip)) {
            QMessageBox::warning(rParentWidget, tr("Warning"),
                                 tr("Cannot open archive \"%1\"\nError %2")
                                 .arg(pFrom).arg(mArchiveFrom.getZipError()));
            return false;
        }
        tArchiveFromList = mArchiveFrom.getFileInfoList64();
    }

    QuaZip mArchiveTo;
    QList<QuaZipFileInfo64> tArchiveToList;

    if (isToDir) {
        QDirIterator iterator(pTo, QDir::Files | QDir::NoDotAndDotDot,
                              QDirIterator::Subdirectories);
        while (iterator.hasNext()) {
            if (mProgress.wasCanceled())
                return false;

            iterator.next();
            tArchiveToList.append(ToZipFileInfo(iterator));
        }
    } else {
        mArchiveTo.setZipName(pTo);
        if (!mArchiveTo.open(QuaZip::mdUnzip)) {
            QMessageBox::warning(rParentWidget, tr("Warning"),
                                 tr("Cannot open archive \"%1\"\nError %2")
                                 .arg(pTo).arg(mArchiveTo.getZipError()));
            return false;
        }
        tArchiveToList = mArchiveTo.getFileInfoList64();
    }

    int tValue = 0;
    mProgress.setMaximum(tArchiveFromList.count() + tArchiveToList.count());

    QList<QuaZipFileInfo64> mNewFiles;
    foreach(QuaZipFileInfo64 rFileTo, tArchiveToList) {
        mProgress.setValue(tValue++);
        if (mProgress.wasCanceled())
            return false;

        bool noNTFSmTime = false;
        QuaZipFileInfo64 rFileFrom = FindFile(rFileTo.name, tArchiveFromList);
        QDateTime rFileFromDate = rFileFrom.getNTFSmTime();
        if (rFileFromDate.isNull()) {
            rFileFromDate = rFileFrom.dateTime;
            noNTFSmTime = true;
        }
        QDateTime rFileToDate = rFileTo.getNTFSmTime();
        if (rFileToDate.isNull()) {
            rFileToDate = rFileTo.dateTime;
            noNTFSmTime = true;
        }
        int tTimeDiff = rFileFromDate.msecsTo(rFileToDate);
        if (tTimeDiff < 0) tTimeDiff *= -1;

        if (rFileFrom.name.isNull() ||           //-- File does not exist.
                noNTFSmTime ? tTimeDiff > 2000 : //-- File mod time is greater than 2 secs (MOE)
                tTimeDiff > 0) {                 //-- With NTFS data, the time is precise.
            mNewFiles.append(rFileTo);
            qDebug() << "ADD:" << rFileTo.name;
            qDebug() << "Difference:" << tTimeDiff;
        }
    }

    QList<QuaZipFileInfo64> mRemoveFiles;
    foreach(QuaZipFileInfo64 rFileFrom, tArchiveFromList) {
        mProgress.setValue(tValue++);
        if (mProgress.wasCanceled())
            return false;

        QuaZipFileInfo64 rFileTo = FindFile(rFileFrom.name, tArchiveToList);
        if (rFileTo.name.isNull()) {    //-- File for deletion.
            mRemoveFiles.append(rFileFrom);
            qDebug() << "REMOVE:" << rFileFrom.name;
        }
    }

    tValue = 0;
    mProgress.setLabelText("Packing...");
    mProgress.setMaximum(mNewFiles.count());

    QuaZip mArchiveSaveAs;
    mArchiveSaveAs.setZipName(pSaveAs);
    mArchiveSaveAs.setFileNameCodec("IBM866");
    if (!mArchiveSaveAs.open(QuaZip::mdCreate)) {
        QMessageBox::warning(rParentWidget, tr("Warning"),
                             tr("Cannot create archive \"%1\"\nError %2")
                             .arg(pSaveAs).arg(mArchiveSaveAs.getZipError()));
        return false;
    }

    QuaZipFile tOutFile(&mArchiveSaveAs);
    foreach(QuaZipFileInfo64 rFileInfo, mNewFiles) {
        mProgress.setValue(tValue++);

        if (!tOutFile.open(QIODevice::WriteOnly, QuaZipNewInfo(rFileInfo.name))) {
            qDebug() << "Cannot create file inside the archive";
        } else {
            if (isToDir) {
                QString tPath = pTo+'/'+rFileInfo.name;
                if (QFileInfo(tPath).isFile()) {
                    QFile tFile(tPath);
                    if (!tFile.open(QIODevice::ReadOnly)) {
                        qDebug() << "Cannot read file outside of archive";
                    } else {
                        tOutFile.write(tFile.readAll());
                        tFile.close();
                    }
                }
            } else {
                QuaZipFile tInFile(&mArchiveTo);
                mArchiveTo.setCurrentFile(rFileInfo.name);
                if (!tInFile.open(QIODevice::ReadOnly)) {
                    qDebug() << "Cannot read file inside the archive";
                } else {
                    tOutFile.write(tInFile.readAll());
                    tInFile.close();
                }
            }
            tOutFile.close();
        }

        if (mProgress.wasCanceled()) {
            mArchiveSaveAs.close();
            QFile::remove(mArchiveSaveAs.getZipName());
            return false;
        }
    }

    mProgress.setLabelText("Finishing...");
    mProgress.setValue(0);
    mProgress.setMaximum(1);

    QBuffer tInfoFile;
    if (!tInfoFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Cannot create buffer";
    } else {
        tInfoFile.setTextModeEnabled(true);
        QTextStream tStream(&tInfoFile);
        foreach(QuaZipFileInfo64 rFileInfo , mRemoveFiles) {
            tStream << "REMOVED \"" << rFileInfo.name << "\"" << endl;
        }
        foreach(QuaZipFileInfo64 rFileInfo , mNewFiles) {
            tStream << "ADDED \"" << rFileInfo.name << "\"" << endl;
        }
        tInfoFile.close();

        if (!tInfoFile.open(QIODevice::ReadOnly)) {
            qDebug() << "Cannot open buffer";
        } else {
            if (!tOutFile.open(QIODevice::WriteOnly, QuaZipNewInfo("CHANGES"))) {
                qDebug() << "Cannot create CHANGES file inside the archive";
            } else {
                tOutFile.write(tInfoFile.readAll());
                tOutFile.close();
            }
            tInfoFile.close();
        }
    }

    if (mArchiveFrom.isOpen())
        mArchiveFrom.close();

    if (mArchiveTo.isOpen())
        mArchiveTo.close();

    mArchiveSaveAs.close();

    qDebug() << "Finished";
    mProgress.setValue(mProgress.maximum());
    return true;
}

/*===================================== PUBLIC SLOTS =====================================*/

/*===================================== PRIVATE SLOTS ====================================*/

/*======================================= PROTECTED ======================================*/

/*======================================== PRIVATE =======================================*/

QuaZipFileInfo64 ArchiveEdit::ToZipFileInfo(const QDirIterator &pIterator)
{
    QuaZipFileInfo64 tInfo;

    QString tBasePath = pIterator.path().replace('\\','/');
    QString tFilePath = pIterator.filePath().replace('\\','/');

    tInfo.name = QString(tFilePath).remove(tBasePath);
    if (tInfo.name.at(0) == '/')
        tInfo.name.remove(0,1);

    QFileInfo tFile(tFilePath);
    tInfo.dateTime = tFile.lastModified();

    if (tFile.isDir()) {
        tInfo.flags = 0;
        tInfo.name += '/';
    } else {
        tInfo.flags = 1;
    }
    return tInfo;
}

QuaZipFileInfo64 ArchiveEdit::FindFile(const QString &pFileName,
                                       const QList<QuaZipFileInfo64> &pArchive)
{
    foreach(QuaZipFileInfo64 rFile, pArchive) {
        if (rFile.name == pFileName)
            return rFile;
    }
    return QuaZipFileInfo64();
}

/*========================================================================================*/
