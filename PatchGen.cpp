/*******************************************************************************************
**
** Project: Patch Generator
** File: PatchGen.cpp
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

#include <QtGui/QApplication>

#include "MainWindow.h"

/*======================================== GLOBAL ========================================*/

int main(int argc, char *argv[])
{
    QApplication mApp(argc, argv);

    QStringList tArguments = mApp.arguments();
    tArguments.takeFirst();

    MainWindow mMainWindow;
    mMainWindow.show();

    if (tArguments.count() >= 3)
        mMainWindow.Start(tArguments.at(0),
                          tArguments.at(1),
                          tArguments.at(2));

    return mApp.exec();
}

/*========================================================================================*/
