#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Point
{
	int x, y;
public:
	void set(int x, int y)
	{
		this->x = x; this->y = y;
	}
	void showPoint()
	{
		cout << "(" << x << "," << y << ")" << endl;
	}

class ColorPoint :
	public Point {
	string color;
public:
	void setColor(string Color) { this->color = color; }
	void showColorPoint() {
		cout << color << ":";
		showPoint();
	}
};

int main()
{
	Point p;
	p.set(100, 101);
	p.showPoint();
	ColorPoint cp;
	cp.set(200, 201);
	cp.setColor("»¡°£¸À");
	cp.showColorPoint();
}