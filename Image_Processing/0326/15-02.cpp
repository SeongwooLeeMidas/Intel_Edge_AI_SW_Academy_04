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
//	cout << "호출 전 --> 원1:" << c1.radius << ",원2:" << c2.radius << endl;
//	swap(c1, c2);
//	cout << "값에 의한 호출 후 --> 원1:" << c1.radius << ",원2:" << c2.radius << endl;
//	swap2(&c1, &c2);
//	cout << "주소에 의한 호출 후 --> 원1:" << c1.radius << ",원2:" << c2.radius << endl;
//	swap3(c1, c2);
//	cout << "주소에 의한 호출 후 --> 원1:" << c1.radius << ",원2:" << c2.radius << endl;
//}