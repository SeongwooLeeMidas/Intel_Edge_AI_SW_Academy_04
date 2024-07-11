#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#define height 5
#define width 7

void main()
{
	int ary[height][width];

	for (int i = 0; i < height; i++)
	{
		int num = 1;
		for (int i = 0; i < height; i++)
		{
			for (int k = 0; k < width; k++)
			{
				printf("%3d ", ary[i][k]);
			}
			printf("\n");
		}
	}
}