#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//int main(void)
//{
//
//	int iSum = 0;
//
//	int i = 0;
//	while (i <= 100)
//	{
//		iSum += i;
//		i += 1;
//	}
//
//	printf("1���� 100������ ���� %d�Դϴ�. \n", iSum);
//
//	return 0;
//}

// while���� ���ѹݺ��� �� ���� ���. ���� for(;;)�� ���ѹݺ� ��밡�������� while ����ϸ� ���

int main(void) 
{
	int iSum = 0;
	int i = 1;

	while (1)
	{
		iSum += i;
		if (iSum >= 100000000)
			break;
		i++;
	}
	
	printf("\n %d", iSum);

	
}