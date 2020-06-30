/*******************************************************************************************
**
** Project: Patch Generator
** File: MainWindow.cpp
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

#include "MainWindow.h"

#include <QtGui/QApplication>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLineEdit>
#include <QtGui/QToolButton>
#include <QtGui/QPushButton>

#include <QtGui/QFileDialog>
#include <QtGui/QKeyEvent>

#include "ArchiveEdit.h"
#include "LineEdit.h"
#include "Global.h"

/*======================================== PUBLIC ========================================*/

MainWindow::MainWindow(QWidget *pParent) :
    QDialog(pParent)
{
    ui.setupUi(this);
    setWindowTitle(QString("%1 %2").arg(APP_PRODUCTNAME).arg(APP_FILEVER));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    connect(ui.mFromButtonZip, SIGNAL(clicked()), this, SLOT(ChooseFromZip()));
    connect(ui.mFromButtonDir, SIGNAL(clicked()), this, SLOT(ChooseFromDir()));
    connect(ui.mToButtonZip, SIGNAL(clicked()), this, SLOT(ChooseToZip()));
    connect(ui.mToButtonDir, SIGNAL(clicked()), this, SLOT(ChooseToDir()));
    connect(ui.mSaveAsButton, SIGNAL(clicked()), this, SLOT(ChooseSaveAs()));
    connect(ui.mStart, SIGNAL(clicked()), this, SLOT(Start()));

    mArchiveEdit = new ArchiveEdit(this);
}

void MainWindow::Start(const QString &pFrom, const QString &pTo, const QString &pSaveAs)
{
    mArchiveEdit->Repackage(pFrom, pTo, pSaveAs);
}

QString MainWindow::GetFrom() const
{
    return ui.mFromLineEdit->text();
}

QString MainWindow::GetTo() const
{
    return ui.mToLineEdit->text();
}

QString MainWindow::GetSaveAs() const
{
    return ui.mSaveAsLineEdit->text();
}

/*===================================== PUBLIC SLOTS =====================================*/

void MainWindow::ChooseFromZip()
{
    QString tPath = GetFrom();
    if (tPath.isEmpty())
        tPath = QDir::currentPath();

    QString rFile = GetFileDialog(tPath);

    if (!rFile.isEmpty())
        ui.mFromLineEdit->setText(rFile);
}

void MainWindow::ChooseFromDir()
{
    QString tPath = GetFrom();
    if (tPath.isEmpty())
        tPath = QDir::currentPath();

    QString rFile = GetDirectoryDialog(tPath);

    if (!rFile.isEmpty())
        ui.mFromLineEdit->setText(rFile);
}

void MainWindow::ChooseToZip()
{
    QString tPath = GetTo();
    if (tPath.isEmpty())
        tPath = QDir::currentPath();

    QString rFile = GetFileDialog(tPath);

    if (!rFile.isEmpty())
        ui.mToLineEdit->setText(rFile);
}

void MainWindow::ChooseToDir()
{
    QString tPath = GetTo();
    if (tPath.isEmpty())
        tPath = QDir::currentPath();

    QString rFile = GetDirectoryDialog(tPath);

    if (!rFile.isEmpty())
        ui.mToLineEdit->setText(rFile);
}

void MainWindow::ChooseSaveAs()
{
    QString tPath = GetSaveAs();
    if (tPath.isEmpty())
        tPath = QDir::currentPath();

    QString rFile = GetSaveDialog(tPath);

    if (!rFile.isEmpty())
        ui.mSaveAsLineEdit->setText(rFile);
}

void MainWindow::Start()
{
    Start(GetFrom(), GetTo(), GetSaveAs());
}

/*===================================== PRIVATE SLOTS ====================================*/

/*======================================= PROTECTED ======================================*/

/*======================================== PRIVATE =======================================*/

QString MainWindow::GetFileDialog(const QString &pPath)
{
    return QFileDialog::getOpenFileName(this, tr("Choose Archive"),
                                        pPath, "zip files (*.zip)");
}

QString MainWindow::GetDirectoryDialog(const QString &pPath)
{
    return QFileDialog::getExistingDirectory(this, tr("Choose Directory"), pPath);
}

QString MainWindow::GetSaveDialog(const QString &pPath)
{
    return QFileDialog::getSaveFileName(this, tr("Save as Archive"),
                                        pPath, "zip file (*.zip)");
}

/*========================================================================================*/
