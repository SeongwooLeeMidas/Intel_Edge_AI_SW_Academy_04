//#include <iostream>
//#include <cstring>
//#include <string>
//using namespace std;
//
//class Circle {
//	/// 클래스의 속성(=성격=특성)
//private :
//	int radius; 
//	int myvar;
//
//	/// 클래스의 기능(=행동=행위)
//public : // 게터/세터
//	inline void setRadius(int radius) { this->radius = radius; };
//	inline void setMyvar(int myvar) { this->myvar = myvar; };
//	// this는 포인터임. 함수의 매개변수와 멤버 변수의 이름이 같을 때, 
//	// 멤버 변수와 함수의 매개변수를 구분하기 위해서 사용
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
//Circle::~Circle() {	cout << "잘자요~~";}
//Circle::Circle() {}
//Circle::Circle(int r) {
//	cout << "새 인스턴스 생성 !!" << endl;
//	radius = r;
//}
//double Circle::getArea() {
//	return radius * radius * 3.14;
//}
//int main() {
//	Circle donutA(1);	
//	Circle donutB;
//	donutB.setRadius(2);
//	cout << "도넛A의 면적은 " << donutA.getArea() << "입니다.";
//	cout << "도넛B의 면적은 " << donutB.getArea() << "입니다.";	
//
//}