#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> 

void main()
{
	int SIZE = 100; // 100Ä­ È®º¸
	int* p;
	p = (int*)malloc(sizeof(int) * 100);

	int iNum = 1234;
	for (int i = 0; i < 100; i++)
	{
		//*(p + i) = iNum;
		p[i] = iNum;
		iNum++;
	}

	long long iSum = 0;
	for (int i = 0; i < SIZE; i++)
		iSum += p[i];
	printf("%ld \n", iSum);

	free(p);
}