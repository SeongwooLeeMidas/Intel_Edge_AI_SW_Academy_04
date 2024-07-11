#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

void main()
{
	#define SIZE 20
	// 배열 준비
	int ary[SIZE];
	// 배열에 값 대입, 소수 20개 찾아서 배열에 넣기

	int count = 0;
	int num = 2;

	while (1) //20개 찾을때까지 무한루프, num이 소수임
	{
		bool sosuYN = true;
		for (int div = 2; div < num; div++)
		{
			if (num % div == 0)
			{
				sosuYN = false;
				break;
			}
		}
		if (sosuYN)
		{
			ary[count] = num;
			count++;
		}
		//20개 다 찾았으면 break
		if (count >= SIZE)
			break;
		num++;
	}
	// (3) 활용하기
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", ary[i]);
	}
	
}