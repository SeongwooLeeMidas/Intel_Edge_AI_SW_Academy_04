#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

void main()
{
	#define SIZE 20
	// �迭 �غ�
	int ary[SIZE];
	// �迭�� �� ����, �Ҽ� 20�� ã�Ƽ� �迭�� �ֱ�

	int count = 0;
	int num = 2;

	while (1) //20�� ã�������� ���ѷ���, num�� �Ҽ���
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
		//20�� �� ã������ break
		if (count >= SIZE)
			break;
		num++;
	}
	// (3) Ȱ���ϱ�
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", ary[i]);
	}
	
}