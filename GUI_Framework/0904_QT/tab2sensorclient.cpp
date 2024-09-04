#include "tab2sensorclient.h"
#include "ui_tab2sensorclient.h"

Tab2SensorClient::Tab2SensorClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab2SensorClient)
{
    ui->setupUi(this);
}

Tab2SensorClient::~Tab2SensorClient()
{
    delete ui;
}
