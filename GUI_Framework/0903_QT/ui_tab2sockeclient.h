/********************************************************************************
** Form generated from reading UI file 'tab2sockeclient.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB2SOCKECLIENT_H
#define UI_TAB2SOCKECLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tab2SockeClient
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *pPBRecvDataClear;
    QPushButton *pPBServerConnect;
    QVBoxLayout *verticalLayout;
    QTextEdit *pTERecvData;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *pLERecvId;
    QLineEdit *pLESendData;
    QPushButton *pPBSendButton;

    void setupUi(QWidget *Tab2SockeClient)
    {
        if (Tab2SockeClient->objectName().isEmpty())
            Tab2SockeClient->setObjectName(QString::fromUtf8("Tab2SockeClient"));
        Tab2SockeClient->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(Tab2SockeClient);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Tab2SockeClient);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        pPBRecvDataClear = new QPushButton(Tab2SockeClient);
        pPBRecvDataClear->setObjectName(QString::fromUtf8("pPBRecvDataClear"));

        horizontalLayout->addWidget(pPBRecvDataClear);

        pPBServerConnect = new QPushButton(Tab2SockeClient);
        pPBServerConnect->setObjectName(QString::fromUtf8("pPBServerConnect"));
        pPBServerConnect->setCheckable(true);

        horizontalLayout->addWidget(pPBServerConnect);

        horizontalLayout->setStretch(0, 8);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pTERecvData = new QTextEdit(Tab2SockeClient);
        pTERecvData->setObjectName(QString::fromUtf8("pTERecvData"));

        verticalLayout->addWidget(pTERecvData);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pLERecvId = new QLineEdit(Tab2SockeClient);
        pLERecvId->setObjectName(QString::fromUtf8("pLERecvId"));

        horizontalLayout_2->addWidget(pLERecvId);

        pLESendData = new QLineEdit(Tab2SockeClient);
        pLESendData->setObjectName(QString::fromUtf8("pLESendData"));

        horizontalLayout_2->addWidget(pLESendData);

        pPBSendButton = new QPushButton(Tab2SockeClient);
        pPBSendButton->setObjectName(QString::fromUtf8("pPBSendButton"));

        horizontalLayout_2->addWidget(pPBSendButton);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 6);
        horizontalLayout_2->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(Tab2SockeClient);
        QObject::connect(pPBRecvDataClear, SIGNAL(clicked()), pTERecvData, SLOT(clear()));

        QMetaObject::connectSlotsByName(Tab2SockeClient);
    } // setupUi

    void retranslateUi(QWidget *Tab2SockeClient)
    {
        Tab2SockeClient->setWindowTitle(QCoreApplication::translate("Tab2SockeClient", "Form", nullptr));
        label->setText(QCoreApplication::translate("Tab2SockeClient", "\354\210\230\354\213\240 \353\215\260\354\235\264\355\204\260", nullptr));
        pPBRecvDataClear->setText(QCoreApplication::translate("Tab2SockeClient", "\354\210\230\354\213\240 \354\202\255\354\240\234", nullptr));
        pPBServerConnect->setText(QCoreApplication::translate("Tab2SockeClient", "\354\204\234\353\262\204 \354\227\260\352\262\260", nullptr));
        pPBSendButton->setText(QCoreApplication::translate("Tab2SockeClient", "\354\206\241\354\213\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tab2SockeClient: public Ui_Tab2SockeClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB2SOCKECLIENT_H
