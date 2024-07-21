#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Circle {
public:
	static int numOfCircles; //�ν��Ͻ� � ����?
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
	cout << "���� �� ��ü ��: " << Circle::getNumofCircles() << endl;
	delete[] p;
	cout << "���� �� ��ü ��: " << Circle::getNumofCircles() << endl;
	
	if (true) 
	{
		Circle a, b;
		cout << "���� �� ��ü ��: " << a.getNumofCircles() << endl;
	}
	cout << "���� �� ��ü ��: " << Circle::getNumofCircles() << endl;
}