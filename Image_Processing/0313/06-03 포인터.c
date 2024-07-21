#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> // GUI 지원 기능

void main()
{
	int a = 100;
	int b = 200;

	printf("변수 a 번지: %x \n", &a);
	printf("변수 b 번지: %x \n", &b);

	short aa[3] = { 10, 20, 30 };

	// 10 = 2034; lvalue는 변수만 올수 있음
	// aa = 2048; 변수만 가능!!
	aa[0] = 111; //이건 변수라 가능
	printf("변수 aa 번지 : %ld \n", aa);
	printf("변수 aa[0]번지 : %ld \n", &aa[01]);

	printf("변수 aa 번지 : %ld \n", aa + 1);
	printf("변수 aa 번지 : %ld \n", &aa[11]);

}

	


}