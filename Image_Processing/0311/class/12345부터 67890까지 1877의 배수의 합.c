#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int i, iSum = 0;

	for (i = 12345; i <= 67890; i++)
		if(i%1877==0)
		iSum += i;

	printf("12345���� 67890���� 1877�� ����� ���� %d�Դϴ�. \n", iSum);

	return 0;
}