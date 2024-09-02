#include <QApplication>
#include <QPushButton>

int main(int argc, char** argv)
{
		QApplication app(argc, argv);

		QPushButton* button = new QPushButton("Quit", 0);
		button->resize(100, 135); // wizet size
		button->move(300, 300); // wizet direction
		button->show();		// Display wizet screen 

		QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));
		return app.exec();		// Qt event loop
}
