#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
	int iSum = 0;
	printf("%d ", 2);
	iSum += 2;

	for (int num = 3; num <= 1000; num += 2)
	{
		// 일단 num을 소수로 가정
		bool sosuYN = true;
		for (int div = 2; div < num; div++) {
			//2부터 그 숫자 앞까지..
			if (num % div == 0)
			{
				sosuYN = false;
				break;
			}
		}
		if (sosuYN == true) 
		{
			printf("%d ", num);
			iSum += num;
		}
	}
	printf("\n2부터 1000까지 소수 합은 %d입니다.\n", iSum);
	
	return 0;
}

// 더 효율적으로 바꿀수 있을까? while문으로 바꿔볼까?