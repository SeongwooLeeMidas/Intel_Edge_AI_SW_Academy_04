#include "tab3sqliteclient.h"
#include "ui_tab3sqliteclient.h"

Tab3SqliteClient::Tab3SqliteClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab3SqliteClient)
{
    ui->setupUi(this);
}

Tab3SqliteClient::~Tab3SqliteClient()
{
    delete ui;
}
