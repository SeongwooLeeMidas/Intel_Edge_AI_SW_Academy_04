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

	p = (int**)malloc(sizeof(int*) * row); //[3][5] 두개니까 포인트 별 2개인거

	for (int i = 0; i < row; i++)
		p[i] = (int*)malloc(sizeof(int) * col); // memory allocation 메모리 할당

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
		free(p[i]); //차례차례 해야함
	free(p);
}