#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> 

void main()
{

	char ch; // 문자형 변수 선언
	char* p; // 문자형 포인터 변수 선언
	ch = 'A';
	p = &ch;

	printf("ch 값: %c \n", ch);
	printf("ch 주소 : %ld \n", &ch);
	printf("p값 : %ld \n", &p);
	printf("p가 가리키는 곳의 실제 값 : %c \n", *p);

	char ch;
	char* p;
	char* q;

	ch = 'A';
	p = &ch;
	q = p;

	*q = 'Z';
	printf("ch값:%c \n", ch);

	// 두 값을 교환하기
	char ch1 = 'A', ch2 = 'Z';
	char* p;
	char* q;

	p = &ch1;
	q = &ch2;

	char tmp;
	tmp = *p;
	*p = q;
	*q = tmp;
	printf("ch1 값 : %c, ch2 값: %c \n", ch1, ch2);

	// 배열과 포인터
	char s[8] = "Basic-C"; //\0
	char* p;

	p = s;

	for (int i = 0; i < 8; i++)
		printf("%c", *(p + i));

}