/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOW_UI_H
#define MAINWINDOW_UI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include "LineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *mGroupFrom;
    QHBoxLayout *mGroupFromLayout;
    LineEdit *mFromLineEdit;
    QToolButton *mFromButtonZip;
    QToolButton *mFromButtonDir;
    QGroupBox *mGroupTo;
    QHBoxLayout *mGroupToLayout;
    LineEdit *mToLineEdit;
    QToolButton *mToButtonZip;
    QToolButton *mToButtonDir;
    QGroupBox *mGroupSaveAs;
    QHBoxLayout *mGroupSaveAsLayout;
    LineEdit *mSaveAsLineEdit;
    QToolButton *mSaveAsButton;
    QPushButton *mStart;

    void setupUi(QDialog *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(330, 218);
        MainWindow->setMinimumSize(QSize(330, 218));
        MainWindow->setMaximumSize(QSize(330, 218));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/PGen.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(MainWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        mGroupFrom = new QGroupBox(MainWindow);
        mGroupFrom->setObjectName(QString::fromUtf8("mGroupFrom"));
        mGroupFromLayout = new QHBoxLayout(mGroupFrom);
        mGroupFromLayout->setObjectName(QString::fromUtf8("mGroupFromLayout"));
        mFromLineEdit = new LineEdit(mGroupFrom);
        mFromLineEdit->setObjectName(QString::fromUtf8("mFromLineEdit"));

        mGroupFromLayout->addWidget(mFromLineEdit);

        mFromButtonZip = new QToolButton(mGroupFrom);
        mFromButtonZip->setObjectName(QString::fromUtf8("mFromButtonZip"));

        mGroupFromLayout->addWidget(mFromButtonZip);

        mFromButtonDir = new QToolButton(mGroupFrom);
        mFromButtonDir->setObjectName(QString::fromUtf8("mFromButtonDir"));

        mGroupFromLayout->addWidget(mFromButtonDir);


        verticalLayout->addWidget(mGroupFrom);

        mGroupTo = new QGroupBox(MainWindow);
        mGroupTo->setObjectName(QString::fromUtf8("mGroupTo"));
        mGroupToLayout = new QHBoxLayout(mGroupTo);
        mGroupToLayout->setObjectName(QString::fromUtf8("mGroupToLayout"));
        mToLineEdit = new LineEdit(mGroupTo);
        mToLineEdit->setObjectName(QString::fromUtf8("mToLineEdit"));

        mGroupToLayout->addWidget(mToLineEdit);

        mToButtonZip = new QToolButton(mGroupTo);
        mToButtonZip->setObjectName(QString::fromUtf8("mToButtonZip"));

        mGroupToLayout->addWidget(mToButtonZip);

        mToButtonDir = new QToolButton(mGroupTo);
        mToButtonDir->setObjectName(QString::fromUtf8("mToButtonDir"));

        mGroupToLayout->addWidget(mToButtonDir);


        verticalLayout->addWidget(mGroupTo);

        mGroupSaveAs = new QGroupBox(MainWindow);
        mGroupSaveAs->setObjectName(QString::fromUtf8("mGroupSaveAs"));
        mGroupSaveAsLayout = new QHBoxLayout(mGroupSaveAs);
        mGroupSaveAsLayout->setObjectName(QString::fromUtf8("mGroupSaveAsLayout"));
        mSaveAsLineEdit = new LineEdit(mGroupSaveAs);
        mSaveAsLineEdit->setObjectName(QString::fromUtf8("mSaveAsLineEdit"));

        mGroupSaveAsLayout->addWidget(mSaveAsLineEdit);

        mSaveAsButton = new QToolButton(mGroupSaveAs);
        mSaveAsButton->setObjectName(QString::fromUtf8("mSaveAsButton"));

        mGroupSaveAsLayout->addWidget(mSaveAsButton);


        verticalLayout->addWidget(mGroupSaveAs);

        mStart = new QPushButton(MainWindow);
        mStart->setObjectName(QString::fromUtf8("mStart"));
        mStart->setDefault(true);

        verticalLayout->addWidget(mStart);


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QDialog *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Patch Generator", 0, QApplication::UnicodeUTF8));
        mGroupFrom->setTitle(QApplication::translate("MainWindow", "From", 0, QApplication::UnicodeUTF8));
        mFromButtonZip->setText(QApplication::translate("MainWindow", "zip", 0, QApplication::UnicodeUTF8));
        mFromButtonDir->setText(QApplication::translate("MainWindow", "dir", 0, QApplication::UnicodeUTF8));
        mGroupTo->setTitle(QApplication::translate("MainWindow", "To", 0, QApplication::UnicodeUTF8));
        mToButtonZip->setText(QApplication::translate("MainWindow", "zip", 0, QApplication::UnicodeUTF8));
        mToButtonDir->setText(QApplication::translate("MainWindow", "dir", 0, QApplication::UnicodeUTF8));
        mGroupSaveAs->setTitle(QApplication::translate("MainWindow", "Save As", 0, QApplication::UnicodeUTF8));
        mSaveAsButton->setText(QApplication::translate("MainWindow", "zip", 0, QApplication::UnicodeUTF8));
        mStart->setText(QApplication::translate("MainWindow", "Generate", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_UI_H
