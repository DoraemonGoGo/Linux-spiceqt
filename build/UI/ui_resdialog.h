/********************************************************************************
** Form generated from reading UI file 'resdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESDIALOG_H
#define UI_RESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ResDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_6;
    QLineEdit *lineEdit_5;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;

    void setupUi(QDialog *ResDialog)
    {
        if (ResDialog->objectName().isEmpty())
            ResDialog->setObjectName(QString::fromUtf8("ResDialog"));
        ResDialog->resize(332, 232);
        ResDialog->setWindowOpacity(0.900000000000000);
        verticalLayout_3 = new QVBoxLayout(ResDialog);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(ResDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setSizeConstraint(QLayout::SetDefaultConstraint);
        label = new QLabel(ResDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(label);

        lineEdit = new QLineEdit(ResDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_7->addWidget(lineEdit);

        pushButton_2 = new QPushButton(ResDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_7->addWidget(pushButton_2);

        pushButton = new QPushButton(ResDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_7->addWidget(pushButton);

        horizontalLayout_7->setStretch(0, 5);
        horizontalLayout_7->setStretch(1, 10);
        horizontalLayout_7->setStretch(2, 1);
        horizontalLayout_7->setStretch(3, 1);

        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_3 = new QLabel(ResDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_8->addWidget(label_3);

        lineEdit_2 = new QLineEdit(ResDialog);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);

        horizontalLayout_8->addWidget(lineEdit_2);

        pushButton_4 = new QPushButton(ResDialog);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
        pushButton_4->setMaximumSize(QSize(1000000, 16777215));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_8->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(ResDialog);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);

        horizontalLayout_8->addWidget(pushButton_3);

        horizontalLayout_8->setStretch(0, 5);
        horizontalLayout_8->setStretch(1, 10);
        horizontalLayout_8->setStretch(2, 1);
        horizontalLayout_8->setStretch(3, 1);

        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_5 = new QLabel(ResDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_9->addWidget(label_5);

        lineEdit_4 = new QLineEdit(ResDialog);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        sizePolicy.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy);

        horizontalLayout_9->addWidget(lineEdit_4);

        pushButton_7 = new QPushButton(ResDialog);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        sizePolicy.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy);
        pushButton_7->setMinimumSize(QSize(0, 0));

        horizontalLayout_9->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(ResDialog);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        sizePolicy.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy);

        horizontalLayout_9->addWidget(pushButton_8);

        horizontalLayout_9->setStretch(0, 5);
        horizontalLayout_9->setStretch(1, 10);

        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(0);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_6 = new QLabel(ResDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_11->addWidget(label_6);

        lineEdit_5 = new QLineEdit(ResDialog);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        sizePolicy.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy);

        horizontalLayout_11->addWidget(lineEdit_5);

        pushButton_9 = new QPushButton(ResDialog);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        sizePolicy.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy);
        pushButton_9->setMinimumSize(QSize(0, 0));

        horizontalLayout_11->addWidget(pushButton_9);

        pushButton_10 = new QPushButton(ResDialog);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        sizePolicy.setHeightForWidth(pushButton_10->sizePolicy().hasHeightForWidth());
        pushButton_10->setSizePolicy(sizePolicy);

        horizontalLayout_11->addWidget(pushButton_10);

        horizontalLayout_11->setStretch(0, 5);
        horizontalLayout_11->setStretch(1, 10);

        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(150);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        pushButton_6 = new QPushButton(ResDialog);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        sizePolicy.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy);

        horizontalLayout_10->addWidget(pushButton_6);

        pushButton_5 = new QPushButton(ResDialog);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        sizePolicy.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy);

        horizontalLayout_10->addWidget(pushButton_5);


        verticalLayout_2->addLayout(horizontalLayout_10);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(ResDialog);

        QMetaObject::connectSlotsByName(ResDialog);
    } // setupUi

    void retranslateUi(QDialog *ResDialog)
    {
        ResDialog->setWindowTitle(QApplication::translate("ResDialog", "Resize guest  to", nullptr));
        label_2->setText(QApplication::translate("ResDialog", "Resize the  guest  display:", nullptr));
        label->setText(QApplication::translate("ResDialog", "width:", nullptr));
        pushButton_2->setText(QApplication::translate("ResDialog", "+", nullptr));
        pushButton->setText(QApplication::translate("ResDialog", "-", nullptr));
        label_3->setText(QApplication::translate("ResDialog", "height:", nullptr));
        pushButton_4->setText(QApplication::translate("ResDialog", "+", nullptr));
        pushButton_3->setText(QApplication::translate("ResDialog", "-", nullptr));
        label_5->setText(QApplication::translate("ResDialog", "    x:", nullptr));
        pushButton_7->setText(QApplication::translate("ResDialog", "+", nullptr));
        pushButton_8->setText(QApplication::translate("ResDialog", "-", nullptr));
        label_6->setText(QApplication::translate("ResDialog", "    y:", nullptr));
        pushButton_9->setText(QApplication::translate("ResDialog", "+", nullptr));
        pushButton_10->setText(QApplication::translate("ResDialog", "-", nullptr));
        pushButton_6->setText(QApplication::translate("ResDialog", "Apply", nullptr));
        pushButton_5->setText(QApplication::translate("ResDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResDialog: public Ui_ResDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESDIALOG_H
