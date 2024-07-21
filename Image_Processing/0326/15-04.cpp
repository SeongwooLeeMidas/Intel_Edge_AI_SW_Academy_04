#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Circle {
public:
	static int numOfCircles; //인스턴스 몇개 생성?
	int radius;

public:
	Circle(int radius=1) 
	{ 
		this->radius = radius;
		numOfCircles++;
	};
	~Circle() {
		numOfCircles--;
	}
	static int getNumofCircles() { return numOfCircles; }

};

int Circle::numOfCircles = 0;

int main()
{
	Circle* p = new Circle[10];
	cout << "현재 원 객체 수: " << Circle::getNumofCircles() << endl;
	delete[] p;
	cout << "현재 원 객체 수: " << Circle::getNumofCircles() << endl;
	
	if (true) 
	{
		Circle a, b;
		cout << "현재 원 객체 수: " << a.getNumofCircles() << endl;
	}
	cout << "현재 원 객체 수: " << Circle::getNumofCircles() << endl;
}