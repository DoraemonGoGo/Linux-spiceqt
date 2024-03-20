/********************************************************************************
** Form generated from reading UI file 'spicemainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPICEMAINWINDOW_H
#define UI_SPICEMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpiceMainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *actionclose;
    QAction *actionCopy_to_guest;
    QAction *actionPaste_to_guest;
    QAction *actionFullscreen;
    QAction *actionToolBar;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *layout;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menuedit;
    QMenu *menuView;
    QMenu *menuInput;
    QMenu *menuOptions;
    QMenu *menuHelp;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *SpiceMainWindow)
    {
        if (SpiceMainWindow->objectName().isEmpty())
            SpiceMainWindow->setObjectName(QString::fromUtf8("SpiceMainWindow"));
        SpiceMainWindow->resize(701, 625);
        action = new QAction(SpiceMainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(SpiceMainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(SpiceMainWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        actionclose = new QAction(SpiceMainWindow);
        actionclose->setObjectName(QString::fromUtf8("actionclose"));
        actionCopy_to_guest = new QAction(SpiceMainWindow);
        actionCopy_to_guest->setObjectName(QString::fromUtf8("actionCopy_to_guest"));
        actionPaste_to_guest = new QAction(SpiceMainWindow);
        actionPaste_to_guest->setObjectName(QString::fromUtf8("actionPaste_to_guest"));
        actionFullscreen = new QAction(SpiceMainWindow);
        actionFullscreen->setObjectName(QString::fromUtf8("actionFullscreen"));
        actionToolBar = new QAction(SpiceMainWindow);
        actionToolBar->setObjectName(QString::fromUtf8("actionToolBar"));
        centralwidget = new QWidget(SpiceMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 701, 561));
        layout = new QVBoxLayout(verticalLayoutWidget);
        layout->setObjectName(QString::fromUtf8("layout"));
        layout->setContentsMargins(0, 0, 0, 0);
        SpiceMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SpiceMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 701, 28));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuedit = new QMenu(menubar);
        menuedit->setObjectName(QString::fromUtf8("menuedit"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuInput = new QMenu(menubar);
        menuInput->setObjectName(QString::fromUtf8("menuInput"));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        SpiceMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SpiceMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SpiceMainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(SpiceMainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        SpiceMainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menuedit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuInput->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menu->addAction(action);
        menu->addAction(action_2);
        menu->addSeparator();
        menu->addAction(actionclose);
        menuedit->addAction(actionCopy_to_guest);
        menuedit->addAction(actionPaste_to_guest);
        menuView->addAction(actionFullscreen);
        menuView->addAction(actionToolBar);

        retranslateUi(SpiceMainWindow);

        QMetaObject::connectSlotsByName(SpiceMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SpiceMainWindow)
    {
        SpiceMainWindow->setWindowTitle(QApplication::translate("SpiceMainWindow", "MainWindow", nullptr));
        action->setText(QApplication::translate("SpiceMainWindow", "connect", nullptr));
        action_2->setText(QApplication::translate("SpiceMainWindow", "recent", nullptr));
        action_3->setText(QApplication::translate("SpiceMainWindow", "\346\217\222\345\205\245", nullptr));
        actionclose->setText(QApplication::translate("SpiceMainWindow", "close", nullptr));
        actionCopy_to_guest->setText(QApplication::translate("SpiceMainWindow", "Copy   to  guest", nullptr));
        actionPaste_to_guest->setText(QApplication::translate("SpiceMainWindow", "Paste to guest", nullptr));
        actionFullscreen->setText(QApplication::translate("SpiceMainWindow", "Fullscreen", nullptr));
        actionToolBar->setText(QApplication::translate("SpiceMainWindow", "ToolBar", nullptr));
        menu->setTitle(QApplication::translate("SpiceMainWindow", "File", nullptr));
        menuedit->setTitle(QApplication::translate("SpiceMainWindow", "Edit", nullptr));
        menuView->setTitle(QApplication::translate("SpiceMainWindow", "View", nullptr));
        menuInput->setTitle(QApplication::translate("SpiceMainWindow", "Input", nullptr));
        menuOptions->setTitle(QApplication::translate("SpiceMainWindow", "Options", nullptr));
        menuHelp->setTitle(QApplication::translate("SpiceMainWindow", "Help", nullptr));
        toolBar->setWindowTitle(QApplication::translate("SpiceMainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpiceMainWindow: public Ui_SpiceMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPICEMAINWINDOW_H
