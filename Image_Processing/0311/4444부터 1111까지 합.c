#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int i, iSum = 0;
	for (i = 1111; i <= 4444; i++)
		iSum += i;
	printf("4444���� 1111������ ���� %d�Դϴ�. \n", iSum);

	return 0;
}