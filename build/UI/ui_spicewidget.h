/********************************************************************************
** Form generated from reading UI file 'spicewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPICEWIDGET_H
#define UI_SPICEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpiceWidget
{
public:
    QAction *actionConnect;
    QAction *actionRcent_Connect;
    QAction *actionClose;
    QAction *actionCopy_From;
    QAction *actionPaste_from_guest;
    QAction *actionFullscreen;
    QAction *actionResize_to;
    QAction *actionToolBar;
    QAction *actionAtatusBar;
    QAction *actionInsert_Smartcard;
    QAction *actionRemove_Smartcard;
    QAction *actionAbout;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menuOptions;
    QMenu *menuHelp;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SpiceWidget)
    {
        if (SpiceWidget->objectName().isEmpty())
            SpiceWidget->setObjectName(QString::fromUtf8("SpiceWidget"));
        SpiceWidget->resize(800, 600);
        actionConnect = new QAction(SpiceWidget);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        actionRcent_Connect = new QAction(SpiceWidget);
        actionRcent_Connect->setObjectName(QString::fromUtf8("actionRcent_Connect"));
        actionClose = new QAction(SpiceWidget);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionCopy_From = new QAction(SpiceWidget);
        actionCopy_From->setObjectName(QString::fromUtf8("actionCopy_From"));
        actionPaste_from_guest = new QAction(SpiceWidget);
        actionPaste_from_guest->setObjectName(QString::fromUtf8("actionPaste_from_guest"));
        actionFullscreen = new QAction(SpiceWidget);
        actionFullscreen->setObjectName(QString::fromUtf8("actionFullscreen"));
        actionResize_to = new QAction(SpiceWidget);
        actionResize_to->setObjectName(QString::fromUtf8("actionResize_to"));
        actionToolBar = new QAction(SpiceWidget);
        actionToolBar->setObjectName(QString::fromUtf8("actionToolBar"));
        actionAtatusBar = new QAction(SpiceWidget);
        actionAtatusBar->setObjectName(QString::fromUtf8("actionAtatusBar"));
        actionInsert_Smartcard = new QAction(SpiceWidget);
        actionInsert_Smartcard->setObjectName(QString::fromUtf8("actionInsert_Smartcard"));
        actionRemove_Smartcard = new QAction(SpiceWidget);
        actionRemove_Smartcard->setObjectName(QString::fromUtf8("actionRemove_Smartcard"));
        actionAbout = new QAction(SpiceWidget);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralwidget = new QWidget(SpiceWidget);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(800, 0));
        centralwidget->setMaximumSize(QSize(15000000, 15000000));
        SpiceWidget->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SpiceWidget);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        SpiceWidget->setMenuBar(menubar);
        toolBar = new QToolBar(SpiceWidget);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        SpiceWidget->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(SpiceWidget);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SpiceWidget->setStatusBar(statusBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menu->addAction(actionConnect);
        menu->addAction(actionRcent_Connect);
        menu->addSeparator();
        menu->addAction(actionClose);
        menu_2->addAction(actionCopy_From);
        menu_2->addAction(actionPaste_from_guest);
        menu_3->addAction(actionFullscreen);
        menu_3->addAction(actionResize_to);
        menu_3->addAction(actionToolBar);
        menu_3->addAction(actionAtatusBar);
        menu_4->addAction(actionInsert_Smartcard);
        menu_4->addAction(actionRemove_Smartcard);
        menuHelp->addAction(actionAbout);

        retranslateUi(SpiceWidget);

        QMetaObject::connectSlotsByName(SpiceWidget);
    } // setupUi

    void retranslateUi(QMainWindow *SpiceWidget)
    {
        SpiceWidget->setWindowTitle(QApplication::translate("SpiceWidget", "MainWindow", nullptr));
        actionConnect->setText(QApplication::translate("SpiceWidget", "Connect", nullptr));
        actionRcent_Connect->setText(QApplication::translate("SpiceWidget", "Rcent Connect", nullptr));
        actionClose->setText(QApplication::translate("SpiceWidget", "Close", nullptr));
        actionCopy_From->setText(QApplication::translate("SpiceWidget", "Copy from guest", nullptr));
        actionPaste_from_guest->setText(QApplication::translate("SpiceWidget", "Paste from guest", nullptr));
        actionFullscreen->setText(QApplication::translate("SpiceWidget", "Fullscreen", nullptr));
        actionResize_to->setText(QApplication::translate("SpiceWidget", "Resize to", nullptr));
        actionToolBar->setText(QApplication::translate("SpiceWidget", "ToolBar", nullptr));
        actionAtatusBar->setText(QApplication::translate("SpiceWidget", "StatusBar", nullptr));
        actionInsert_Smartcard->setText(QApplication::translate("SpiceWidget", "Insert Smartcard", nullptr));
        actionRemove_Smartcard->setText(QApplication::translate("SpiceWidget", "Remove Smartcard", nullptr));
        actionAbout->setText(QApplication::translate("SpiceWidget", "About...", nullptr));
        menu->setTitle(QApplication::translate("SpiceWidget", "File", nullptr));
        menu_2->setTitle(QApplication::translate("SpiceWidget", "Edit", nullptr));
        menu_3->setTitle(QApplication::translate("SpiceWidget", "View", nullptr));
        menu_4->setTitle(QApplication::translate("SpiceWidget", "Input", nullptr));
        menuOptions->setTitle(QApplication::translate("SpiceWidget", "Options", nullptr));
        menuHelp->setTitle(QApplication::translate("SpiceWidget", "Help", nullptr));
        toolBar->setWindowTitle(QApplication::translate("SpiceWidget", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpiceWidget: public Ui_SpiceWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPICEWIDGET_H
