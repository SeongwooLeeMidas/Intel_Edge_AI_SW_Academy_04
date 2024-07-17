#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

////////////////////
///// 전역 변수부
////////////////////

FILE* rfp;
char fileName[200] = "D:/RAW/Etc_Raw(squre)/LENNA512.raw";
#define height 512
#define width 512

// 메모리 확보
unsigned char inImage[height][width], outImage[height][width];


////////////////////
///// 함수 선언부
////////////////////
void loadImage(); int getIntValue(); void printImage();
void addImage(int); void equalImage(); 

void main()
{ //이미지 파일에서 메모리로 로딩!
	loadImage(); //함수 호출!

	// 영상처리 알고리즘 구현
	// (1) 밝게 하기 (= 숫자 더하기)
	int value = getIntValue();
	addImage(value);

}


////////////////////
///// 함수 정의부
////////////////////


/// 공통 함수

void printImage() 
{
	for (int i = height/2 - 5; i < height/2 + 5; i++) {
		for (int k = width/2 - 5; k < width/2 + 5; k++) {
			printf("%3d ", outImage[i][k]);
		}
		printf("\n");
	}
	printf("\n");
}

void loadImage()
{
	rfp = fopen(fileName, "rb");
	fread(inImage, sizeof(unsigned char), height * width, rfp);
	fclose(rfp);
	equalImage();
}

int getIntValue()
{
	int retValue;
	printf("정수값 --> ");
	scanf("%d", &retValue);

	return retValue;

}


/// 영상처리 함수
void equalImage()  // 동일영상 알고리즘
{  // 입력 배열 --> 출력 배열
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			outImage[i][k] = inImage[i][k];
		}
	}
	printImage();
}

void addImage(int val)   // 더하기 알고리즘
{
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			if (inImage[i][k] + val < 255)
				outImage[i][k] = inImage[i][k] + val;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();
}