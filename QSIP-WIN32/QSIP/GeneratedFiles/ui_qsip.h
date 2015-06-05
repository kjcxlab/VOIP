/********************************************************************************
** Form generated from reading UI file 'qsip.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSIP_H
#define UI_QSIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QSIPClass
{
public:
    QGroupBox *groupBox;
    QLineEdit *lineEdit_Callee;
    QLabel *label_Call_Status;
    QPushButton *pushButton_Dial;
    QPushButton *pushButton_Hang;
    QPushButton *pushButton_Dtmf;
    QLineEdit *lineEdit_Dtmf;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit_Host;
    QLabel *label;
    QLineEdit *lineEdit_Name;
    QLabel *label_2;
    QLineEdit *lineEdit_Pwd;
    QLabel *label_3;
    QLineEdit *lineEdit_Port;
    QLabel *label_4;
    QPushButton *pushButton_Reg;
    QPushButton *pushButton_Unreg;
    QLabel *label_Reg_Status;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QPushButton *pushButton_10;
    QPushButton *pushButton_6;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QPushButton *pushButton_13;
    QPushButton *pushButton_2;
    QPushButton *pushButton_8;
    QPushButton *pushButton_7;
    QPushButton *pushButton_9;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;

    void setupUi(QWidget *QSIPClass)
    {
        if (QSIPClass->objectName().isEmpty())
            QSIPClass->setObjectName(QStringLiteral("QSIPClass"));
        QSIPClass->resize(404, 570);
        groupBox = new QGroupBox(QSIPClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 190, 381, 101));
        lineEdit_Callee = new QLineEdit(groupBox);
        lineEdit_Callee->setObjectName(QStringLiteral("lineEdit_Callee"));
        lineEdit_Callee->setGeometry(QRect(10, 20, 191, 31));
        label_Call_Status = new QLabel(groupBox);
        label_Call_Status->setObjectName(QStringLiteral("label_Call_Status"));
        label_Call_Status->setGeometry(QRect(10, 60, 191, 31));
        label_Call_Status->setFrameShape(QFrame::WinPanel);
        label_Call_Status->setFrameShadow(QFrame::Sunken);
        pushButton_Dial = new QPushButton(groupBox);
        pushButton_Dial->setObjectName(QStringLiteral("pushButton_Dial"));
        pushButton_Dial->setGeometry(QRect(210, 20, 75, 31));
        pushButton_Hang = new QPushButton(groupBox);
        pushButton_Hang->setObjectName(QStringLiteral("pushButton_Hang"));
        pushButton_Hang->setGeometry(QRect(300, 20, 75, 31));
        pushButton_Dtmf = new QPushButton(groupBox);
        pushButton_Dtmf->setObjectName(QStringLiteral("pushButton_Dtmf"));
        pushButton_Dtmf->setGeometry(QRect(300, 60, 75, 31));
        lineEdit_Dtmf = new QLineEdit(groupBox);
        lineEdit_Dtmf->setObjectName(QStringLiteral("lineEdit_Dtmf"));
        lineEdit_Dtmf->setGeometry(QRect(210, 60, 71, 31));
        groupBox_2 = new QGroupBox(QSIPClass);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 20, 381, 161));
        lineEdit_Host = new QLineEdit(groupBox_2);
        lineEdit_Host->setObjectName(QStringLiteral("lineEdit_Host"));
        lineEdit_Host->setGeometry(QRect(110, 30, 141, 31));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 91, 31));
        lineEdit_Name = new QLineEdit(groupBox_2);
        lineEdit_Name->setObjectName(QStringLiteral("lineEdit_Name"));
        lineEdit_Name->setGeometry(QRect(70, 80, 121, 31));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(-20, 80, 91, 31));
        lineEdit_Pwd = new QLineEdit(groupBox_2);
        lineEdit_Pwd->setObjectName(QStringLiteral("lineEdit_Pwd"));
        lineEdit_Pwd->setGeometry(QRect(240, 80, 121, 31));
        lineEdit_Pwd->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        lineEdit_Pwd->setDragEnabled(false);
        lineEdit_Pwd->setReadOnly(false);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(190, 81, 51, 31));
        lineEdit_Port = new QLineEdit(groupBox_2);
        lineEdit_Port->setObjectName(QStringLiteral("lineEdit_Port"));
        lineEdit_Port->setGeometry(QRect(300, 30, 61, 31));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(260, 30, 41, 31));
        pushButton_Reg = new QPushButton(groupBox_2);
        pushButton_Reg->setObjectName(QStringLiteral("pushButton_Reg"));
        pushButton_Reg->setGeometry(QRect(30, 120, 75, 31));
        pushButton_Unreg = new QPushButton(groupBox_2);
        pushButton_Unreg->setObjectName(QStringLiteral("pushButton_Unreg"));
        pushButton_Unreg->setGeometry(QRect(120, 120, 75, 31));
        label_Reg_Status = new QLabel(groupBox_2);
        label_Reg_Status->setObjectName(QStringLiteral("label_Reg_Status"));
        label_Reg_Status->setGeometry(QRect(240, 120, 121, 31));
        label_Reg_Status->setFrameShape(QFrame::WinPanel);
        label_Reg_Status->setFrameShadow(QFrame::Sunken);
        label_Reg_Status->setLineWidth(1);
        groupBox_3 = new QGroupBox(QSIPClass);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 300, 381, 261));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_10 = new QPushButton(groupBox_3);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        sizePolicy.setHeightForWidth(pushButton_10->sizePolicy().hasHeightForWidth());
        pushButton_10->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_10, 4, 0, 1, 1);

        pushButton_6 = new QPushButton(groupBox_3);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        sizePolicy.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_6, 1, 2, 1, 1);

        pushButton = new QPushButton(groupBox_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_3 = new QPushButton(groupBox_3);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_3, 0, 2, 1, 1);

        pushButton_5 = new QPushButton(groupBox_3);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        sizePolicy.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_5, 1, 1, 1, 1);

        pushButton_4 = new QPushButton(groupBox_3);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_4, 1, 0, 1, 1);

        pushButton_13 = new QPushButton(groupBox_3);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        sizePolicy.setHeightForWidth(pushButton_13->sizePolicy().hasHeightForWidth());
        pushButton_13->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_13, 7, 1, 1, 1);

        pushButton_2 = new QPushButton(groupBox_3);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_8 = new QPushButton(groupBox_3);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        sizePolicy.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_8, 2, 1, 1, 1);

        pushButton_7 = new QPushButton(groupBox_3);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        sizePolicy.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_7, 2, 0, 1, 1);

        pushButton_9 = new QPushButton(groupBox_3);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        sizePolicy.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_9, 2, 2, 1, 1);

        pushButton_11 = new QPushButton(groupBox_3);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        sizePolicy.setHeightForWidth(pushButton_11->sizePolicy().hasHeightForWidth());
        pushButton_11->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_11, 4, 1, 1, 1);

        pushButton_12 = new QPushButton(groupBox_3);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        sizePolicy.setHeightForWidth(pushButton_12->sizePolicy().hasHeightForWidth());
        pushButton_12->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_12, 4, 2, 1, 1);


        retranslateUi(QSIPClass);

        QMetaObject::connectSlotsByName(QSIPClass);
    } // setupUi

    void retranslateUi(QWidget *QSIPClass)
    {
        QSIPClass->setWindowTitle(QApplication::translate("QSIPClass", "QSIP", 0));
        groupBox->setTitle(QApplication::translate("QSIPClass", "\347\224\250\346\210\267\345\220\215", 0));
        lineEdit_Callee->setText(QApplication::translate("QSIPClass", "\347\274\226\350\276\221", 0));
        label_Call_Status->setText(QApplication::translate("QSIPClass", "<html><head/><body><p>(\345\260\261\347\273\252..)</p></body></html>", 0));
        pushButton_Dial->setText(QApplication::translate("QSIPClass", "\345\221\274\345\217\253", 0));
        pushButton_Hang->setText(QApplication::translate("QSIPClass", "\346\214\202\346\226\255", 0));
        pushButton_Dtmf->setText(QApplication::translate("QSIPClass", "DTMF", 0));
        lineEdit_Dtmf->setText(QApplication::translate("QSIPClass", "\347\274\226\350\276\221", 0));
        groupBox_2->setTitle(QApplication::translate("QSIPClass", "\346\210\221\347\232\204\350\264\246\346\210\267", 0));
        lineEdit_Host->setText(QApplication::translate("QSIPClass", "59.74.168.146", 0));
        label->setText(QApplication::translate("QSIPClass", "<html><head/><body><p align=\"right\">\345\234\260\345\235\200(IP/\345\237\237\345\220\215)\357\274\232</p></body></html>", 0));
        lineEdit_Name->setText(QApplication::translate("QSIPClass", "105", 0));
        label_2->setText(QApplication::translate("QSIPClass", "<html><head/><body><p align=\"right\">\347\224\250\346\210\267\345\220\215\357\274\232</p></body></html>", 0));
        lineEdit_Pwd->setText(QApplication::translate("QSIPClass", "105", 0));
        label_3->setText(QApplication::translate("QSIPClass", "<html><head/><body><p align=\"right\">\345\257\206    \347\240\201\357\274\232</p></body></html>", 0));
        lineEdit_Port->setText(QApplication::translate("QSIPClass", "5060", 0));
        label_4->setText(QApplication::translate("QSIPClass", "<html><head/><body><p align=\"right\">\347\253\257\345\217\243\357\274\232</p></body></html>", 0));
        pushButton_Reg->setText(QApplication::translate("QSIPClass", "\347\231\273\345\275\225", 0));
        pushButton_Unreg->setText(QApplication::translate("QSIPClass", "\346\263\250\351\224\200", 0));
        label_Reg_Status->setText(QApplication::translate("QSIPClass", "<html><head/><body><p>\346\234\252\347\231\273\345\275\225</p></body></html>", 0));
        groupBox_3->setTitle(QApplication::translate("QSIPClass", "\346\213\250\345\217\267", 0));
        pushButton_10->setText(QApplication::translate("QSIPClass", "*", 0));
        pushButton_6->setText(QApplication::translate("QSIPClass", "6", 0));
        pushButton->setText(QApplication::translate("QSIPClass", "1", 0));
        pushButton_3->setText(QApplication::translate("QSIPClass", "3", 0));
        pushButton_5->setText(QApplication::translate("QSIPClass", "5", 0));
        pushButton_4->setText(QApplication::translate("QSIPClass", "4", 0));
        pushButton_13->setText(QApplication::translate("QSIPClass", "\346\270\205\347\251\272", 0));
        pushButton_2->setText(QApplication::translate("QSIPClass", "2", 0));
        pushButton_8->setText(QApplication::translate("QSIPClass", "8", 0));
        pushButton_7->setText(QApplication::translate("QSIPClass", "7", 0));
        pushButton_9->setText(QApplication::translate("QSIPClass", "9", 0));
        pushButton_11->setText(QApplication::translate("QSIPClass", "0", 0));
        pushButton_12->setText(QApplication::translate("QSIPClass", "#", 0));
    } // retranslateUi

};

namespace Ui {
    class QSIPClass: public Ui_QSIPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSIP_H
