//#include <iostream>
//#include <cstring>
//#include <string>
//using namespace std;
//
//class Circle {
//	/// Ŭ������ �Ӽ�(=����=Ư��)
//private :
//	int radius; 
//	int myvar;
//
//	/// Ŭ������ ���(=�ൿ=����)
//public : // ����/����
//	inline void setRadius(int radius) { this->radius = radius; };
//	inline void setMyvar(int myvar) { this->myvar = myvar; };
//	// this�� ��������. �Լ��� �Ű������� ��� ������ �̸��� ���� ��, 
//	// ��� ������ �Լ��� �Ű������� �����ϱ� ���ؼ� ���
//	inline int getRadius() { return radius; };
//	inline int getMyvar() ;
//public :
//	Circle();
//	Circle(int) ;
//	~Circle();
//	double getArea() ;
//};
//
//int Circle::getMyvar() {
//	return myvar;
//}
//Circle::~Circle() {	cout << "���ڿ�~~";}
//Circle::Circle() {}
//Circle::Circle(int r) {
//	cout << "�� �ν��Ͻ� ���� !!" << endl;
//	radius = r;
//}
//double Circle::getArea() {
//	return radius * radius * 3.14;
//}
//int main() {
//	Circle donutA(1);	
//	Circle donutB;
//	donutB.setRadius(2);
//	cout << "����A�� ������ " << donutA.getArea() << "�Դϴ�.";
//	cout << "����B�� ������ " << donutB.getArea() << "�Դϴ�.";	
//
//}