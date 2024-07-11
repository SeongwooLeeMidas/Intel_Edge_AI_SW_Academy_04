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
//	printf("1에서 100까지의 합은 %d입니다. \n", iSum);
//
//	return 0;
//}

// while문은 무한반복할 때 많이 사용. 물론 for(;;)로 무한반복 사용가능하지만 while 사용하면 깔끔

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