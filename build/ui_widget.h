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
#include <QtWidgets/QTextBrowser>
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
    QLineEdit *tlsportedit;
    QLabel *tlsportlabel;
    QLabel *reconlabel;
    QTextBrowser *recontext;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(326, 647);
        ipedit = new QLineEdit(Widget);
        ipedit->setObjectName(QString::fromUtf8("ipedit"));
        ipedit->setGeometry(QRect(130, 20, 181, 41));
        iplabel = new QLabel(Widget);
        iplabel->setObjectName(QString::fromUtf8("iplabel"));
        iplabel->setGeometry(QRect(20, 20, 101, 41));
        portlabel = new QLabel(Widget);
        portlabel->setObjectName(QString::fromUtf8("portlabel"));
        portlabel->setGeometry(QRect(20, 90, 101, 41));
        portedit = new QLineEdit(Widget);
        portedit->setObjectName(QString::fromUtf8("portedit"));
        portedit->setGeometry(QRect(130, 90, 181, 41));
        cancelbtn = new QPushButton(Widget);
        cancelbtn->setObjectName(QString::fromUtf8("cancelbtn"));
        cancelbtn->setGeometry(QRect(70, 590, 101, 41));
        connbtn = new QPushButton(Widget);
        connbtn->setObjectName(QString::fromUtf8("connbtn"));
        connbtn->setGeometry(QRect(210, 590, 101, 41));
        tlsportedit = new QLineEdit(Widget);
        tlsportedit->setObjectName(QString::fromUtf8("tlsportedit"));
        tlsportedit->setGeometry(QRect(130, 160, 181, 41));
        tlsportlabel = new QLabel(Widget);
        tlsportlabel->setObjectName(QString::fromUtf8("tlsportlabel"));
        tlsportlabel->setGeometry(QRect(20, 160, 101, 41));
        reconlabel = new QLabel(Widget);
        reconlabel->setObjectName(QString::fromUtf8("reconlabel"));
        reconlabel->setGeometry(QRect(10, 220, 171, 41));
        recontext = new QTextBrowser(Widget);
        recontext->setObjectName(QString::fromUtf8("recontext"));
        recontext->setGeometry(QRect(10, 260, 301, 311));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        iplabel->setText(QApplication::translate("Widget", "<html><head/><body><p><span style=\" font-size:12pt;\">Hostname</span></p></body></html>", nullptr));
        portlabel->setText(QApplication::translate("Widget", "<html><head/><body><p><span style=\" font-size:12pt;\">Port</span></p></body></html>", nullptr));
        cancelbtn->setText(QApplication::translate("Widget", "Cancel", nullptr));
        connbtn->setText(QApplication::translate("Widget", "Connect", nullptr));
        tlsportlabel->setText(QApplication::translate("Widget", "<html><head/><body><p><span style=\" font-size:12pt;\">TLS Port</span></p></body></html>", nullptr));
        reconlabel->setText(QApplication::translate("Widget", "<html><head/><body><p><span style=\" font-size:12pt;\">Recent connection:</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
