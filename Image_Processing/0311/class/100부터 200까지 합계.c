#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//int main(void)
//{
//	int i, iSum = 0;
//	for (int i = 100; i <= 200; i++)
//	{
//		iSum += i;
//	}
//		printf("100���� 200������ ���� %d�Դϴ�.\n", iSum);
//	
//	return 0;
//}

int main(void)
{
	int i = 100;
	int iSum = 0;

	while (i <= 200)
	{
		iSum += i;
		i += 1;
	}

	printf("100���� 200���� ���� %d�Դϴ�.\n", iSum);

	return 0;
}