#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> 

void main()
{
	int row = 3;
	int col = 5;

	// int p[row][col];

	int** p;

	p = (int**)malloc(sizeof(int*) * row); //[3][5] �ΰ��ϱ� ����Ʈ �� 2���ΰ�

	for (int i = 0; i < row; i++)
		p[i] = (int*)malloc(sizeof(int) * col); // memory allocation �޸� �Ҵ�

	int value = 1;
	for (int i = 0; i < row; i++)
	{
		for (int k = 0; k < col; k++)
		{
			printf("%d ", p[i][k]);
		}
		puts("");
	}

	for (int i = 0; i < row; i++)
		free(p[i]); //�������� �ؾ���
	free(p);
}