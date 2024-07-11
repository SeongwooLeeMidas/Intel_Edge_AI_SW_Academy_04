#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int i, iSum = 0;
	for (i = 1111; i <= 4444; i++)
		iSum += i;
	printf("4444부터 1111까지의 합은 %d입니다. \n", iSum);

	return 0;
}