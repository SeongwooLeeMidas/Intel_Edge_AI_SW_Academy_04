#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> 

void main()
{

	char ch; // ������ ���� ����
	char* p; // ������ ������ ���� ����
	ch = 'A';
	p = &ch;

	printf("ch ��: %c \n", ch);
	printf("ch �ּ� : %ld \n", &ch);
	printf("p�� : %ld \n", &p);
	printf("p�� ����Ű�� ���� ���� �� : %c \n", *p);

	char ch;
	char* p;
	char* q;

	ch = 'A';
	p = &ch;
	q = p;

	*q = 'Z';
	printf("ch��:%c \n", ch);

	// �� ���� ��ȯ�ϱ�
	char ch1 = 'A', ch2 = 'Z';
	char* p;
	char* q;

	p = &ch1;
	q = &ch2;

	char tmp;
	tmp = *p;
	*p = q;
	*q = tmp;
	printf("ch1 �� : %c, ch2 ��: %c \n", ch1, ch2);

	// �迭�� ������
	char s[8] = "Basic-C"; //\0
	char* p;

	p = s;

	for (int i = 0; i < 8; i++)
		printf("%c", *(p + i));

}