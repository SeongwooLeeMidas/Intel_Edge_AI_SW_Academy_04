#include <QApplication>
#include <QPushButton>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QPushButton *button = new QPushButton("Quit", 0);
    button->resize(180, 135); 		/* 위젯의 크기 설정 */
    button->move(300, 300);		/* 위젯의 위치 설정 */
    button->show(); 			/* 위젯의 화면 표시 */

	QObject::connect(button,SIGNAL(clicked()),&app,SLOT(quit()));
    return app.exec();			/* Qt의 이벤트 루프 시작 */
}
