#include <iostream>
#include <cstring>
#include <string>
//using std::cout;
//using std::endl;
using namespace std;

class Circle 
{
	// Ŭ������ �Ӽ� (=����=Ư��)
public:
	int radius; 
	int myvar;
	
	// Ŭ������ ���
public:	// ����/����
	void setRadius(int value) { radius = value; };
	void setMyvar(int value) { myvar = value; };
	int getRadius() { return radius; };
	int getMyvar() { return myvar; };

public:
	Circle();
	Circle(int);	
	~Circle();	//�Ҹ���
	double getArea();
};

Circle::Circle() {
	cout << "���ڿ�~";
}

Circle::Circle(int r) {
	cout << "�� �ν��Ͻ� ����!!" << endl;
	radius = r;
}

double Circle::getArea()
{
	return 3.14 * radius * radius;
}

int main()
{
	Circle donutA(1);

	Circle donutB;
	donutB.setRadius(2);
	//double area = donut.getArea();
	cout << "����A�� ������ " << donutA.getArea() << "�Դϴ�." << endl;
	cout << "����B�� ������ " << donutB.getArea() << "�Դϴ�." << endl;

	Circle pizza;
	pizza.radius = 30;
	area = pizza.getArea();
	cout << "������ ������ " << area << "�Դϴ�." << endl;

	return 0;
}