/********************************************************************************
** Form generated from reading UI file 'tab1devcontrol.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB1DEVCONTROL_H
#define UI_TAB1DEVCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tab1DevControl
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pPBtimerStart;
    QComboBox *pCBtimerValue;
    QPushButton *pPBQuit;
    QHBoxLayout *horizontalLayout_2;
    QDial *pDialLed;
    QLCDNumber *pLcdNumberLed;
    QHBoxLayout *horizontalLayout_3;
    QProgressBar *pProgressBarLed;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *gridLayout;
    QCheckBox *pCBkey6;
    QCheckBox *pCBkey8;
    QCheckBox *pCBkey2;
    QCheckBox *pCBkey3;
    QCheckBox *pCBkey7;
    QCheckBox *pCBkey4;
    QCheckBox *pCBkey5;
    QCheckBox *pCBkey1;
    QHBoxLayout *horizontalLayout_5;
    QLCDNumber *pLcdNumberKey;

    void setupUi(QWidget *Tab1DevControl)
    {
        if (Tab1DevControl->objectName().isEmpty())
            Tab1DevControl->setObjectName(QString::fromUtf8("Tab1DevControl"));
        Tab1DevControl->resize(473, 358);
        verticalLayout = new QVBoxLayout(Tab1DevControl);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pPBtimerStart = new QPushButton(Tab1DevControl);
        pPBtimerStart->setObjectName(QString::fromUtf8("pPBtimerStart"));
        pPBtimerStart->setCheckable(true);
        pPBtimerStart->setChecked(false);

        horizontalLayout->addWidget(pPBtimerStart);

        pCBtimerValue = new QComboBox(Tab1DevControl);
        pCBtimerValue->addItem(QString());
        pCBtimerValue->addItem(QString());
        pCBtimerValue->addItem(QString());
        pCBtimerValue->addItem(QString());
        pCBtimerValue->addItem(QString());
        pCBtimerValue->setObjectName(QString::fromUtf8("pCBtimerValue"));

        horizontalLayout->addWidget(pCBtimerValue);

        pPBQuit = new QPushButton(Tab1DevControl);
        pPBQuit->setObjectName(QString::fromUtf8("pPBQuit"));

        horizontalLayout->addWidget(pPBQuit);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pDialLed = new QDial(Tab1DevControl);
        pDialLed->setObjectName(QString::fromUtf8("pDialLed"));
        pDialLed->setMaximum(255);
        pDialLed->setValue(0);
        pDialLed->setWrapping(true);
        pDialLed->setNotchesVisible(true);

        horizontalLayout_2->addWidget(pDialLed);

        pLcdNumberLed = new QLCDNumber(Tab1DevControl);
        pLcdNumberLed->setObjectName(QString::fromUtf8("pLcdNumberLed"));
        pLcdNumberLed->setDigitCount(2);
        pLcdNumberLed->setMode(QLCDNumber::Hex);
        pLcdNumberLed->setSegmentStyle(QLCDNumber::Filled);

        horizontalLayout_2->addWidget(pLcdNumberLed);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pProgressBarLed = new QProgressBar(Tab1DevControl);
        pProgressBarLed->setObjectName(QString::fromUtf8("pProgressBarLed"));
        pProgressBarLed->setMaximum(255);
        pProgressBarLed->setValue(0);

        horizontalLayout_3->addWidget(pProgressBarLed);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pCBkey6 = new QCheckBox(Tab1DevControl);
        pCBkey6->setObjectName(QString::fromUtf8("pCBkey6"));

        gridLayout->addWidget(pCBkey6, 0, 2, 1, 1);

        pCBkey8 = new QCheckBox(Tab1DevControl);
        pCBkey8->setObjectName(QString::fromUtf8("pCBkey8"));

        gridLayout->addWidget(pCBkey8, 0, 0, 1, 1);

        pCBkey2 = new QCheckBox(Tab1DevControl);
        pCBkey2->setObjectName(QString::fromUtf8("pCBkey2"));

        gridLayout->addWidget(pCBkey2, 1, 2, 1, 1);

        pCBkey3 = new QCheckBox(Tab1DevControl);
        pCBkey3->setObjectName(QString::fromUtf8("pCBkey3"));

        gridLayout->addWidget(pCBkey3, 1, 1, 1, 1);

        pCBkey7 = new QCheckBox(Tab1DevControl);
        pCBkey7->setObjectName(QString::fromUtf8("pCBkey7"));

        gridLayout->addWidget(pCBkey7, 0, 1, 1, 1);

        pCBkey4 = new QCheckBox(Tab1DevControl);
        pCBkey4->setObjectName(QString::fromUtf8("pCBkey4"));

        gridLayout->addWidget(pCBkey4, 1, 0, 1, 1);

        pCBkey5 = new QCheckBox(Tab1DevControl);
        pCBkey5->setObjectName(QString::fromUtf8("pCBkey5"));

        gridLayout->addWidget(pCBkey5, 0, 3, 1, 1);

        pCBkey1 = new QCheckBox(Tab1DevControl);
        pCBkey1->setObjectName(QString::fromUtf8("pCBkey1"));

        gridLayout->addWidget(pCBkey1, 1, 3, 1, 1);


        horizontalLayout_4->addLayout(gridLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pLcdNumberKey = new QLCDNumber(Tab1DevControl);
        pLcdNumberKey->setObjectName(QString::fromUtf8("pLcdNumberKey"));
        pLcdNumberKey->setDigitCount(2);
        pLcdNumberKey->setMode(QLCDNumber::Hex);
        pLcdNumberKey->setSegmentStyle(QLCDNumber::Filled);

        horizontalLayout_5->addWidget(pLcdNumberKey);


        horizontalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_4);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 4);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 4);

        retranslateUi(Tab1DevControl);
        QObject::connect(pDialLed, SIGNAL(valueChanged(int)), pProgressBarLed, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(Tab1DevControl);
    } // setupUi

    void retranslateUi(QWidget *Tab1DevControl)
    {
        Tab1DevControl->setWindowTitle(QCoreApplication::translate("Tab1DevControl", "Form", nullptr));
        pPBtimerStart->setText(QCoreApplication::translate("Tab1DevControl", "TimerStart", nullptr));
        pCBtimerValue->setItemText(0, QCoreApplication::translate("Tab1DevControl", "50", nullptr));
        pCBtimerValue->setItemText(1, QCoreApplication::translate("Tab1DevControl", "100", nullptr));
        pCBtimerValue->setItemText(2, QCoreApplication::translate("Tab1DevControl", "500", nullptr));
        pCBtimerValue->setItemText(3, QCoreApplication::translate("Tab1DevControl", "1000", nullptr));
        pCBtimerValue->setItemText(4, QCoreApplication::translate("Tab1DevControl", "2000", nullptr));

        pPBQuit->setText(QCoreApplication::translate("Tab1DevControl", "Quit", nullptr));
        pCBkey6->setText(QCoreApplication::translate("Tab1DevControl", "6", nullptr));
        pCBkey8->setText(QCoreApplication::translate("Tab1DevControl", "8", nullptr));
        pCBkey2->setText(QCoreApplication::translate("Tab1DevControl", "2", nullptr));
        pCBkey3->setText(QCoreApplication::translate("Tab1DevControl", "3", nullptr));
        pCBkey7->setText(QCoreApplication::translate("Tab1DevControl", "7", nullptr));
        pCBkey4->setText(QCoreApplication::translate("Tab1DevControl", "4", nullptr));
        pCBkey5->setText(QCoreApplication::translate("Tab1DevControl", "5", nullptr));
        pCBkey1->setText(QCoreApplication::translate("Tab1DevControl", "1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tab1DevControl: public Ui_Tab1DevControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB1DEVCONTROL_H
