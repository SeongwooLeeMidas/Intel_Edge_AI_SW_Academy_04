#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

//int main(void)
//{
//	// 5개짜리 배열을 준비하고, 값을 100부터 104까지 대입
//
//	const int SIZE = 5;
//
//	int ary[5];
//	int num = 100;
//
//	for (int i = 0; i < 5; i++)
//	{
//		ary[i] = num;
//		num++;
//	}
//
//	return 0;
//
//	// 퀴즈: 배열 10개를 준비하고, 5부터 5의 배수를 대입, 그리고 배열의 합계
//} 

void main()
{
	int ary[10];
	int num = 5;

	for (int i = 0; i < 10; i++)
	{
		ary[i] = num;
		num += 5;
	}

	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		sum += ary[i];
	}

	printf("합은 %d 입니다.\n", sum);
} 

//10번에 9번은 이 구조를 사용함. 가장 기본적인 구조.
// 퀴즈: 배열 20개 준비하고 2부터 소수를 20개 저장. 그리고 배열 내용 출력.


