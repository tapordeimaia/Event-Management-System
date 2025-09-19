/********************************************************************************
** Form generated from reading UI file 'QtLifeAfterSchool.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTLIFEAFTERSCHOOL_H
#define UI_QTLIFEAFTERSCHOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtLifeAfterSchoolClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtLifeAfterSchoolClass)
    {
        if (QtLifeAfterSchoolClass->objectName().isEmpty())
            QtLifeAfterSchoolClass->setObjectName("QtLifeAfterSchoolClass");
        QtLifeAfterSchoolClass->resize(600, 400);
        menuBar = new QMenuBar(QtLifeAfterSchoolClass);
        menuBar->setObjectName("menuBar");
        QtLifeAfterSchoolClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtLifeAfterSchoolClass);
        mainToolBar->setObjectName("mainToolBar");
        QtLifeAfterSchoolClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtLifeAfterSchoolClass);
        centralWidget->setObjectName("centralWidget");
        QtLifeAfterSchoolClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtLifeAfterSchoolClass);
        statusBar->setObjectName("statusBar");
        QtLifeAfterSchoolClass->setStatusBar(statusBar);

        retranslateUi(QtLifeAfterSchoolClass);

        QMetaObject::connectSlotsByName(QtLifeAfterSchoolClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtLifeAfterSchoolClass)
    {
        QtLifeAfterSchoolClass->setWindowTitle(QCoreApplication::translate("QtLifeAfterSchoolClass", "QtLifeAfterSchool", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtLifeAfterSchoolClass: public Ui_QtLifeAfterSchoolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTLIFEAFTERSCHOOL_H
