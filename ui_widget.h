/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLineEdit *ipedit;
    QLabel *iplabel;
    QLabel *portlabel;
    QLineEdit *portedit;
    QPushButton *cancelbtn;
    QPushButton *connbtn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(326, 647);
        ipedit = new QLineEdit(Widget);
        ipedit->setObjectName(QString::fromUtf8("ipedit"));
        ipedit->setGeometry(QRect(110, 20, 181, 41));
        iplabel = new QLabel(Widget);
        iplabel->setObjectName(QString::fromUtf8("iplabel"));
        iplabel->setGeometry(QRect(20, 20, 101, 41));
        portlabel = new QLabel(Widget);
        portlabel->setObjectName(QString::fromUtf8("portlabel"));
        portlabel->setGeometry(QRect(20, 90, 101, 41));
        portedit = new QLineEdit(Widget);
        portedit->setObjectName(QString::fromUtf8("portedit"));
        portedit->setGeometry(QRect(110, 90, 181, 41));
        cancelbtn = new QPushButton(Widget);
        cancelbtn->setObjectName(QString::fromUtf8("cancelbtn"));
        cancelbtn->setGeometry(QRect(70, 590, 101, 41));
        connbtn = new QPushButton(Widget);
        connbtn->setObjectName(QString::fromUtf8("connbtn"));
        connbtn->setGeometry(QRect(210, 590, 101, 41));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        iplabel->setText(QApplication::translate("Widget", "Hostname", nullptr));
        portlabel->setText(QApplication::translate("Widget", "Port", nullptr));
        cancelbtn->setText(QApplication::translate("Widget", "Cancel", nullptr));
        connbtn->setText(QApplication::translate("Widget", "Connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
