//#include <iostream>
//#include <cstring>
//#include <string>
//using namespace std;
//
//class Circle {
//public:
//	int radius;
//public:
//	Circle(int radius) { this->radius = radius; };
//};
//
//void swap(Circle a, Circle b) {
//	Circle tmp(0);
//	tmp.radius = a.radius;
//	a.radius = b.radius;
//	b.radius = tmp.radius;
//}
//
//void swap2(Circle *a, Circle *b) {
//	Circle tmp(0);
//	tmp.radius = a->radius;
//	a->radius = b->radius;
//	b->radius = tmp.radius;
//}
//
//void swap3(Circle& a, Circle& b) {
//	Circle tmp(0);
//	tmp.radius = a.radius;
//	a.radius = b.radius;
//	b.radius = tmp.radius;
//}
//
//int main() 
//{
//	Circle c1(100), c2(200);
//	cout << "ȣ�� �� --> ��1:" << c1.radius << ",��2:" << c2.radius << endl;
//	swap(c1, c2);
//	cout << "���� ���� ȣ�� �� --> ��1:" << c1.radius << ",��2:" << c2.radius << endl;
//	swap2(&c1, &c2);
//	cout << "�ּҿ� ���� ȣ�� �� --> ��1:" << c1.radius << ",��2:" << c2.radius << endl;
//	swap3(c1, c2);
//	cout << "�ּҿ� ���� ȣ�� �� --> ��1:" << c1.radius << ",��2:" << c2.radius << endl;
//}