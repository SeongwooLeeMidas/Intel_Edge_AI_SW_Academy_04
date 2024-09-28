/********************************************************************************
** Form generated from reading UI file 'testwebview.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTWEBVIEW_H
#define UI_TESTWEBVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestWebView
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *pTab1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *pQVBoxLayout1_1;
    QVBoxLayout *pQVBoxLayout1_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *pQVBoxLayout2_1;
    QVBoxLayout *pQVBoxLayout2_2;
    QWidget *pTab2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *pQVBoxLayout2;

    void setupUi(QWidget *TestWebView)
    {
        if (TestWebView->objectName().isEmpty())
            TestWebView->setObjectName(QString::fromUtf8("TestWebView"));
        TestWebView->resize(890, 629);
        verticalLayout_2 = new QVBoxLayout(TestWebView);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(TestWebView);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        pTab1 = new QWidget();
        pTab1->setObjectName(QString::fromUtf8("pTab1"));
        verticalLayout = new QVBoxLayout(pTab1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pQVBoxLayout1_1 = new QVBoxLayout();
        pQVBoxLayout1_1->setObjectName(QString::fromUtf8("pQVBoxLayout1_1"));

        horizontalLayout->addLayout(pQVBoxLayout1_1);

        pQVBoxLayout1_2 = new QVBoxLayout();
        pQVBoxLayout1_2->setObjectName(QString::fromUtf8("pQVBoxLayout1_2"));

        horizontalLayout->addLayout(pQVBoxLayout1_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pQVBoxLayout2_1 = new QVBoxLayout();
        pQVBoxLayout2_1->setObjectName(QString::fromUtf8("pQVBoxLayout2_1"));

        horizontalLayout_2->addLayout(pQVBoxLayout2_1);

        pQVBoxLayout2_2 = new QVBoxLayout();
        pQVBoxLayout2_2->setObjectName(QString::fromUtf8("pQVBoxLayout2_2"));

        horizontalLayout_2->addLayout(pQVBoxLayout2_2);


        verticalLayout->addLayout(horizontalLayout_2);

        tabWidget->addTab(pTab1, QString());
        pTab2 = new QWidget();
        pTab2->setObjectName(QString::fromUtf8("pTab2"));
        verticalLayout_4 = new QVBoxLayout(pTab2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        pQVBoxLayout2 = new QVBoxLayout();
        pQVBoxLayout2->setObjectName(QString::fromUtf8("pQVBoxLayout2"));

        verticalLayout_4->addLayout(pQVBoxLayout2);

        tabWidget->addTab(pTab2, QString());

        verticalLayout_2->addWidget(tabWidget);


        retranslateUi(TestWebView);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TestWebView);
    } // setupUi

    void retranslateUi(QWidget *TestWebView)
    {
        TestWebView->setWindowTitle(QCoreApplication::translate("TestWebView", "TestWebView", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(pTab1), QCoreApplication::translate("TestWebView", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(pTab2), QCoreApplication::translate("TestWebView", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestWebView: public Ui_TestWebView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWEBVIEW_H
