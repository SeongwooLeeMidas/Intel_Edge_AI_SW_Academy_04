#include <iostream>
#include <cstring>
#include <string>
//using std::cout;
//using std::endl;
using namespace std;

class Circle 
{
	// 클래스의 속성 (=성격=특성)
public:
	int radius; 
	int myvar;
	
	// 클래스의 기능
public:	// 게터/세터
	void setRadius(int value) { radius = value; };
	void setMyvar(int value) { myvar = value; };
	int getRadius() { return radius; };
	int getMyvar() { return myvar; };

public:
	Circle();
	Circle(int);	
	~Circle();	//소멸자
	double getArea();
};

Circle::Circle() {
	cout << "잘자요~";
}

Circle::Circle(int r) {
	cout << "새 인스턴스 생성!!" << endl;
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
	cout << "도넛A의 면적은 " << donutA.getArea() << "입니다." << endl;
	cout << "도넛B의 면적은 " << donutB.getArea() << "입니다." << endl;

	Circle pizza;
	pizza.radius = 30;
	area = pizza.getArea();
	cout << "피자의 면적은 " << area << "입니다." << endl;

	return 0;
}