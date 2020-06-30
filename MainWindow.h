/*******************************************************************************************
**
** Project: Patch Generator
** File: MainWindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "generated/MainWindow_ui.h"

/*======================================== CLASSES =======================================*/

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
class QToolButton;
class QPushButton;
QT_END_NAMESPACE

class ArchiveEdit;
class LineEdit;

class MainWindow : public QDialog
{
        Q_OBJECT

    public:
        MainWindow(QWidget *pParent = 0);

        void Start(const QString &pFrom,
                   const QString &pTo,
                   const QString &pSaveAs);

        QString GetFrom() const;
        QString GetTo() const;
        QString GetSaveAs() const;

    public slots:
        void ChooseFromZip();
        void ChooseFromDir();
        void ChooseToZip();
        void ChooseToDir();
        void ChooseSaveAs();
        void Start();

    private slots:

    signals:

    protected:

    private:
        Ui_MainWindow ui;

        ArchiveEdit *mArchiveEdit;

        QString GetFileDialog(const QString &pPath);
        QString GetDirectoryDialog(const QString &pPath);
        QString GetSaveDialog(const QString &pPath);
};

#endif // MAINWINDOW_H

/*========================================================================================*/
