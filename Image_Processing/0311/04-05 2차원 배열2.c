#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#define height 3
#define width 5

void main()
{	//2차원 배열 
	//(0) 배열 준비
	int ary[height][width];

	// (1) 배열에 값을 불러오기 (나중엔 그림파일 읽어오기)
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			ary[i][k] = 100;
		}
	}
	// (2) 배열을 처리하기(=활용하기)
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			ary[i][k] += 10; // 10만큼 밝게 처리!
		}
	}
	// (3) 배열 출력하기(=영상을 화면에 디스플레이)
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			printf("%3d ", ary[i][k]);
		}
		printf("\n");
	}
	// 5x7 크기의 배열 준비하고, 배열에 1,2,3 .. 값을 채우기
	// 배열의 값을 모두 2배로 하고, 배열을 출력하기
}

