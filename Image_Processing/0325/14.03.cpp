#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int main()
{
	cout << "�� ��?";
	int n;
	cin >> n;
	int* p = new int[n]; //���� �迭(=���� �迭)

	for (int i = 0; i < n; i++)
		p[i] = 100;

	for (int i = 0; i < n; i++)
		cout << p[i] << " ";


	delete[] p;

	int height, width;
	cout << "��?";
	cin >> height;
	cout << "��?";
	cin >> width;

	// �Է��� ũ���� 2���� int�� �迭 ����� ����, ���� ��� 127�� �ʱ�ȭ
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