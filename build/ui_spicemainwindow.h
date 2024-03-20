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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpiceMainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SpiceMainWindow)
    {
        if (SpiceMainWindow->objectName().isEmpty())
            SpiceMainWindow->setObjectName(QString::fromUtf8("SpiceMainWindow"));
        SpiceMainWindow->resize(800, 600);
        action = new QAction(SpiceMainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(SpiceMainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(SpiceMainWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        centralwidget = new QWidget(SpiceMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        SpiceMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SpiceMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        SpiceMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SpiceMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SpiceMainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(action);
        menu->addAction(action_2);
        menu_2->addAction(action_3);

        retranslateUi(SpiceMainWindow);

        QMetaObject::connectSlotsByName(SpiceMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SpiceMainWindow)
    {
        SpiceMainWindow->setWindowTitle(QApplication::translate("SpiceMainWindow", "MainWindow", nullptr));
        action->setText(QApplication::translate("SpiceMainWindow", "\345\244\215\345\210\266", nullptr));
        action_2->setText(QApplication::translate("SpiceMainWindow", "\347\262\230\350\264\264", nullptr));
        action_3->setText(QApplication::translate("SpiceMainWindow", "\346\217\222\345\205\245", nullptr));
        menu->setTitle(QApplication::translate("SpiceMainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QApplication::translate("SpiceMainWindow", "\347\274\226\350\276\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpiceMainWindow: public Ui_SpiceMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPICEMAINWINDOW_H
