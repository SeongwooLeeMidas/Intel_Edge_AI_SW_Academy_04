#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> // GUI ���� ���

void main()
{
	int a = 100;
	int b = 200;

	printf("���� a ����: %x \n", &a);
	printf("���� b ����: %x \n", &b);

	short aa[3] = { 10, 20, 30 };

	// 10 = 2034; lvalue�� ������ �ü� ����
	// aa = 2048; ������ ����!!
	aa[0] = 111; //�̰� ������ ����
	printf("���� aa ���� : %ld \n", aa);
	printf("���� aa[0]���� : %ld \n", &aa[01]);

	printf("���� aa ���� : %ld \n", aa + 1);
	printf("���� aa ���� : %ld \n", &aa[11]);

}

	


}