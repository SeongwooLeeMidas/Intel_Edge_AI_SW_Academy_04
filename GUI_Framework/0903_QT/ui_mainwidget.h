/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *pTabWidget;
    QWidget *pTab1;
    QWidget *pTab2;
    QWidget *pTab3;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(466, 370);
        verticalLayout = new QVBoxLayout(MainWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pTabWidget = new QTabWidget(MainWidget);
        pTabWidget->setObjectName(QString::fromUtf8("pTabWidget"));
        pTab1 = new QWidget();
        pTab1->setObjectName(QString::fromUtf8("pTab1"));
        pTabWidget->addTab(pTab1, QString());
        pTab2 = new QWidget();
        pTab2->setObjectName(QString::fromUtf8("pTab2"));
        pTabWidget->addTab(pTab2, QString());
        pTab3 = new QWidget();
        pTab3->setObjectName(QString::fromUtf8("pTab3"));
        pTabWidget->addTab(pTab3, QString());

        verticalLayout->addWidget(pTabWidget);


        retranslateUi(MainWidget);

        pTabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QCoreApplication::translate("MainWidget", "MainWidget", nullptr));
        pTabWidget->setTabText(pTabWidget->indexOf(pTab1), QCoreApplication::translate("MainWidget", "Tab 1", nullptr));
        pTabWidget->setTabText(pTabWidget->indexOf(pTab2), QCoreApplication::translate("MainWidget", "Tab 2", nullptr));
        pTabWidget->setTabText(pTabWidget->indexOf(pTab3), QCoreApplication::translate("MainWidget", "Tab3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
