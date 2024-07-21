#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int main()
{
	cout << "몇 개?";
	int n;
	cin >> n;
	int* p = new int[n]; //동적 배열(=가변 배열)

	for (int i = 0; i < n; i++)
		p[i] = 100;

	for (int i = 0; i < n; i++)
		cout << p[i] << " ";


	delete[] p;

	int height, width;
	cout << "행?";
	cin >> height;
	cout << "열?";
	cin >> width;

	// 입력한 크기의 2차원 int형 배열 만들고 해제, 값은 모두 127로 초기화
	int** array;

	array = new int* [height];
	for (int i = 0; i < height; i++)
		array[i] = new int[width];

	for (int i = 0; i < height; i++)
		for (int k = 0; k < width; k++)
			array[i][k] = 127;

	for (int i = 0; i < height; i++)
		delete array[i];
	delete[] array;

	



}