#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//int main(void)
//{
//	int i, iSum = 0;
//
//	for (i = 2; i <= 1000; i += 2)
//		iSum += i;
//
//	printf("1���� 1000������ ¦���� ���� %d�Դϴ�. \n", iSum);
//}

int main(void)
{
	int i = 0;
	int iSum = 0;
	
	while (i <= 1000)
	{
		iSum += i;
		i = i + 2;
	}
	printf("1���� 1000���� ¦���� ���� %d�Դϴ�. \n",iSum);

	return 0;
}