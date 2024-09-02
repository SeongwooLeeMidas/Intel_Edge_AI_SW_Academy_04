#include <QApplication>
#include <QPushButton>
#include <QLabel>

#include "CustomWidget.h"

CustomWidget::CustomWidget(QWidget* parent) : QWidget(parent)
{
		QLabel* hello = new QLabel("<font color=blue>Hello <i>World!</i></font>", this);
		hello->resize(180, 35); // wizet button size
		
		QPushButton* button = new QPushButton("Quit", this);
		button->resize(120, 35); // wizet button size
		button->move(0, 40);

		this->resize(240, 170); //  wizet custom size
		this->move(300, 300); // wizet direction

//		QObject::connect(button, SIGNAL(clicked()), qApp, SLOT(quit()));
		QObject::connect(button, SIGNAL(clicked()), this, SLOT(processClick()));
		QObject::connect(this, SIGNAL(widgetClicked()), qApp, SLOT(quit));
}

void CustomWidget::processClick()
{
		emit widgetClicked();
//		qApp->quit();
}
