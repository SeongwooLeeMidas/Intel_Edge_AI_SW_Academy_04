#include <iostream>
#include <cstring>
#include <string>
//using std::cout;
//using std::endl;
using namespace std;

int main()
{
	//// cout << "Hello" << endl << "World~" << 3.14;
	//cout << "너비?";
	//int width;
	//cin >> width;

	////cout << "입력한 너비는 " << width << "입니다.";

	//char password[11];

	//cout << "암호?";
	//// cin >> password;
	//cin.getline(password, 11, '\n');

	//cout << "입력한 암호는 " << password << "입니다.";
	
	string song("안녕하세요? 방가방가~");
	string elvis("엘비스 프레슬리");

	cout << "노래 불러!" << song + "라라" << endl << "누가 불러?" << elvis;


	return 0;
}