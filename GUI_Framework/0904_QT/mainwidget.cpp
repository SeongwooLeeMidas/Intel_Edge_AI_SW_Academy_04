#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    pTab1SocketClient = new Tab1SocketClient(ui->pTab1);
    ui->pTab1->setLayout(pTab1SocketClient->layout());
    pTab2SensorClient = new Tab2SensorClient(ui->pTab2);
    ui->pTab2->setLayout(pTab2SensorClient->layout());
    pTab3SqliteClient = new Tab3SqliteClient(ui->pTab3);
    ui->pTab3->setLayout(pTab3SqliteClient->layout());
}

MainWidget::~MainWidget()
{
    delete ui;
}

