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
		// �ϴ� num�� �Ҽ��� ����
		bool sosuYN = true;
		for (int div = 2; div < num; div++) {
			//2���� �� ���� �ձ���..
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
	printf("\n2���� 1000���� �Ҽ� ���� %d�Դϴ�.\n", iSum);
	
	return 0;
}

// �� ȿ�������� �ٲܼ� ������? while������ �ٲ㺼��?