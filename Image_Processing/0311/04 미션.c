#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void main()
{
	srand((unsigned int)time(0)); //시계 초기화

	// 선택한 영상의 크기만큼 메모리 확보 작업
#define height 7
#define width 7

// 2차원 배열 준비, 메모리 할당
	unsigned char image[height][width];

	// 이미지 파일을 2차원 배열로 로딩
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			image[i][k] = rand() % 256;
		}
	}

	// 원본 출력
	printf("원본 이미지를 출력합니다.\n");
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			printf("%3d ", image[i][k]);
		}
		puts("");
	}

	// 이미지를 반전해서 출력
	printf("\n이미지를 반전해서 출력합니다.\n");
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			image[i][k] = 255 - image[i][k];
		}		
	}

	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			printf("%3d ", image[i][k]);
		}
		puts("");
	}


	// 영상처리 효과 (흑백처리, 0과 255만 존재)
	printf("\n흑백으로 처리하여 출력합니다.\n");
	
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			if (image[i][k] - 127 >= 0)
				image[i][k] = 0;
			else
				image[i][k] = 255;
		}
	}

	// 결과 이미지 출력	
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			printf("%3d ", image[i][k]);
		}
		puts("");
	}
}