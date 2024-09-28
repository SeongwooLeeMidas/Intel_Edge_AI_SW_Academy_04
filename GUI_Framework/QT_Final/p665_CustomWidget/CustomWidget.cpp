#include <QApplication>
#include <QPushButton>
#include <QLabel>

#include "CustomWidget.h"

CustomWidget::CustomWidget(QWidget* parent) : QWidget(parent)
{

	QLabel *hello = new QLabel("<font color=blue>Hello <i>World!</i></font>", this);
    hello->resize(180, 35);        /* 위젯의 크기 설정 */

    QPushButton *button = new QPushButton("Quit", this);
    button->resize(120, 35); 		/* 위젯의 크기 설정 */
    button->move(0, 40); 		/* 위젯의 크기 설정 */

	this->resize(240, 170);
    this->move(300, 300);		/* 위젯의 위치 설정 */

	QObject::connect(button,SIGNAL(clicked()),qApp,SLOT(quit()));
}
