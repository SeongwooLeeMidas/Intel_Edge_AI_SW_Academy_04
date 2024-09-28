#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //  QObject::connect(button,SIGNAL(clicked()),qApp,SLOT(quit()));
    QObject::connect(ui->button,SIGNAL(clicked()),this,SLOT(processClick()));
    QObject::connect(this,SIGNAL(widgetClicked()),qApp,SLOT(quit()));
}
void Widget::processClick()
{
//    emit widgetClicked();
    //  qApp->quit();

    ui->hello->setText("Hi!");
}

Widget::~Widget()
{
    delete ui;
}

