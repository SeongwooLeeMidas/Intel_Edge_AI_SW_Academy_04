#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// (0) 선택한 영상의 가로 세로
#define height 5
#define width 5

// (1) 메모리(2차원 배열 준비)
unsigned char image[height][width];

//함수 선언부와 정의부
void loadImage()
{
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			image[i][k] = rand() % 256;
		}
	}
}
void printImage()
{
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			printf("%3d ", image[i][k]);
		}
		puts("");
	}
	puts("");
}
void reverseImage()
{
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			image[i][k] = 255 - image[i][k];
		}	
	}
}
void addImage(int val)
{
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			if (image[i][k] + val < 256)
				image[i][k] += val;
			else
				image[i][k] = 255;
		}
	}
}


void main()
{
	// 랜덤 초기화
	srand((unsigned int)(time)(0)); // 시계 초기화
	//이미지 파일 --> 2차원 배열로 로딩
	loadImage();
	// 원본 출력
	printImage();
	// 3-1 영상 반전 처리
	reverseImage();
	// 3-2 영상 밝게 처리
	int value;
	printf("밝게할 값 --> ");
	scanf("%d", &value);
	addImage(value);
}