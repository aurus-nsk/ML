/********************************************************************************
** Form generated from reading UI file 'mywindow.ui'
**
** Created: Mon 25. Jun 12:58:02 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWINDOW_H
#define UI_MYWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myWindow
{
public:
    QAction *action_Exit;
    QAction *actionLinear_regression;
    QAction *actionAbout;
    QWidget *centralWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *myWindow)
    {
        if (myWindow->objectName().isEmpty())
            myWindow->setObjectName(QString::fromUtf8("myWindow"));
        myWindow->resize(920, 600);
        action_Exit = new QAction(myWindow);
        action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Exit->setIcon(icon);
        actionLinear_regression = new QAction(myWindow);
        actionLinear_regression->setObjectName(QString::fromUtf8("actionLinear_regression"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/gear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLinear_regression->setIcon(icon1);
        actionAbout = new QAction(myWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/ksirc.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon2);
        centralWidget = new QWidget(myWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        myWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(myWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        myWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(myWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        myWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionLinear_regression);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionAbout);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_Exit);

        retranslateUi(myWindow);

        QMetaObject::connectSlotsByName(myWindow);
    } // setupUi

    void retranslateUi(QMainWindow *myWindow)
    {
        myWindow->setWindowTitle(QApplication::translate("myWindow", "myWindow", 0, QApplication::UnicodeUTF8));
        action_Exit->setText(QApplication::translate("myWindow", "&Exit", 0, QApplication::UnicodeUTF8));
        actionLinear_regression->setText(QApplication::translate("myWindow", "Linear regression", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("myWindow", "About", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class myWindow: public Ui_myWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWINDOW_H
