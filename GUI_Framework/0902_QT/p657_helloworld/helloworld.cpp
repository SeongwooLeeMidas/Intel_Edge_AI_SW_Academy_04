#include <QApplication>
#include <QLabel>

int main(int argc, char** argv)
{
		QApplication app(argc, argv);

		QLabel* hello = new QLabel("<font color=blue>Hello <i>World!</i></font>", 0);
		hello->resize(80, 35); // wizet size
		hello->move(300, 300); // wizet direction
		hello->show();		// Display wizet screen 

		return app.exec();		// Qt event loop
}
