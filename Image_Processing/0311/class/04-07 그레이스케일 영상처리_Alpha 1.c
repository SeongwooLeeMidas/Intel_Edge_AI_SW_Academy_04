#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void main()
{
	srand((unsigned int)time(0)); //별거 아니고 시계 초기화
	// (0) 선택한 영상의 크기만큼 메모리를 확보하는 것(jolly.raw: 10x10 이미지로 가정한다면)
	#define height 10
	#define width 10

	// (1) 2차원 배열(=메모리) 준비
	unsigned char image[height][width];

	// (2) 이미지 파일 --> 2차원 배열로 로딩(Loading)
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			image[i][k] = rand() % 256;
		}
	}

	// 원본 이미지 출력, 작업은 다 한거임. 
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			printf("%3d ", image[i][k]);
		}
		printf("\n");
	}

	// (3) 영상처리 효과 (Image Processing)
	// (3-1) 밝게하기 알고리즘 (50 정도)
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			if (image[i][k] + 50 < 256) //일반적으로 8비트고, 256가지
				image[i][k] += 50;
			else
				image[i][k] += 255;
		}
	}

	// (3-2) 어둡게 알고리즘 (50 정도)
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			if(image[i][k] - 50 >0)
				image[i][k] -= 50;
			else
				image[i][k] = 0;

		}
	}

	// 결과 이미지 출력
	printf("\n");
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			printf("%3d ", image[i][k]);
		}
		printf("\n");
	}
}