/*******************************************************************************************
**
** Project: Patch Generator
** File: ArchiveEdit.h
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

#ifndef ARCHIVEEDIT_H
#define ARCHIVEEDIT_H

#include <QtCore/QObject>

/*======================================== CLASSES =======================================*/

QT_BEGIN_NAMESPACE
class QDirIterator;
QT_END_NAMESPACE

class QuaZipFileInfo64;

class ArchiveEdit : public QObject
{
        Q_OBJECT

    public:
        ArchiveEdit(QWidget *pParent);

        bool Repackage(const QString &pFrom,
                       const QString &pTo,
                       const QString &pSaveAs);

    public slots:

    private slots:

    signals:

    protected:

    private:
        QWidget *rParentWidget;

        QuaZipFileInfo64 ToZipFileInfo(const QDirIterator &pIterator);
        QuaZipFileInfo64 FindFile(const QString &pFileName,
                                  const QList<QuaZipFileInfo64> &pArchive);
};

#endif // ARCHIVEEDIT_H

/*========================================================================================*/
