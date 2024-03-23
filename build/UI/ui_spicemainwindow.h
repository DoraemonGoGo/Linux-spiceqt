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
    QAction *actionStatusBar;
    QAction *actiontoolclose;
    QAction *actiontoolcopy;
    QAction *actiontoolpaste;
    QAction *actiontoolfullscreen;
    QAction *actionResize_to;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *layout;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menuedit;
    QMenu *menuView;
    QMenu *menuInput;
    QMenu *menuOptions;
    QMenu *menuHelp;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *SpiceMainWindow)
    {
        if (SpiceMainWindow->objectName().isEmpty())
            SpiceMainWindow->setObjectName(QString::fromUtf8("SpiceMainWindow"));
        SpiceMainWindow->resize(608, 597);
        action = new QAction(SpiceMainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(SpiceMainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(SpiceMainWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        actionclose = new QAction(SpiceMainWindow);
        actionclose->setObjectName(QString::fromUtf8("actionclose"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("close");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(":/icon/\350\255\246\347\244\272\347\272\242\345\217\211.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionclose->setIcon(icon);
        actionCopy_to_guest = new QAction(SpiceMainWindow);
        actionCopy_to_guest->setObjectName(QString::fromUtf8("actionCopy_to_guest"));
        actionPaste_to_guest = new QAction(SpiceMainWindow);
        actionPaste_to_guest->setObjectName(QString::fromUtf8("actionPaste_to_guest"));
        actionFullscreen = new QAction(SpiceMainWindow);
        actionFullscreen->setObjectName(QString::fromUtf8("actionFullscreen"));
        actionFullscreen->setCheckable(true);
        QIcon icon1;
        iconThemeName = QString::fromUtf8("fullscreen");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(":/icon/fullscreen.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionFullscreen->setIcon(icon1);
        actionToolBar = new QAction(SpiceMainWindow);
        actionToolBar->setObjectName(QString::fromUtf8("actionToolBar"));
        actionToolBar->setCheckable(true);
        actionStatusBar = new QAction(SpiceMainWindow);
        actionStatusBar->setObjectName(QString::fromUtf8("actionStatusBar"));
        actionStatusBar->setCheckable(true);
        actiontoolclose = new QAction(SpiceMainWindow);
        actiontoolclose->setObjectName(QString::fromUtf8("actiontoolclose"));
        actiontoolclose->setIcon(icon);
        actiontoolcopy = new QAction(SpiceMainWindow);
        actiontoolcopy->setObjectName(QString::fromUtf8("actiontoolcopy"));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("copy");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8(":/icon/\345\244\215\345\210\266.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actiontoolcopy->setIcon(icon2);
        actiontoolpaste = new QAction(SpiceMainWindow);
        actiontoolpaste->setObjectName(QString::fromUtf8("actiontoolpaste"));
        QIcon icon3;
        iconThemeName = QString::fromUtf8("paste");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8(":/icon/\347\262\230\350\264\264.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actiontoolpaste->setIcon(icon3);
        actiontoolfullscreen = new QAction(SpiceMainWindow);
        actiontoolfullscreen->setObjectName(QString::fromUtf8("actiontoolfullscreen"));
        actiontoolfullscreen->setIcon(icon1);
        actionResize_to = new QAction(SpiceMainWindow);
        actionResize_to->setObjectName(QString::fromUtf8("actionResize_to"));
        centralwidget = new QWidget(SpiceMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        layout = new QVBoxLayout();
        layout->setObjectName(QString::fromUtf8("layout"));

        verticalLayout->addLayout(layout);

        SpiceMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SpiceMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 608, 28));
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
        statusBar = new QStatusBar(SpiceMainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SpiceMainWindow->setStatusBar(statusBar);
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
        menuView->addAction(actionStatusBar);
        toolBar->addAction(actiontoolclose);
        toolBar->addSeparator();
        toolBar->addAction(actiontoolcopy);
        toolBar->addAction(actiontoolpaste);
        toolBar->addSeparator();
        toolBar->addAction(actiontoolfullscreen);
        toolBar->addSeparator();
        toolBar->addAction(actionResize_to);

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
        actionStatusBar->setText(QApplication::translate("SpiceMainWindow", "StatusBar", nullptr));
        actiontoolclose->setText(QApplication::translate("SpiceMainWindow", "toolclose", nullptr));
        actiontoolcopy->setText(QApplication::translate("SpiceMainWindow", "toolcopy", nullptr));
        actiontoolpaste->setText(QApplication::translate("SpiceMainWindow", "toolpaste", nullptr));
        actiontoolfullscreen->setText(QApplication::translate("SpiceMainWindow", "toolfullscreen", nullptr));
        actionResize_to->setText(QApplication::translate("SpiceMainWindow", "Resize to", nullptr));
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
