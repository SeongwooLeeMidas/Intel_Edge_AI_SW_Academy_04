#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

//////////////
// 전역 변수부
//////////////

FILE* rfp;
char fileName[200] = "D:/RAW/Etc_Raw(squre)/LENNA512.raw";
#define height 512
#define width 512

// 메모리 확보
unsigned char inImage[height][width], outImage[height][width];


////////////////
// 함수의 선언부
//////////////// 
void loadImage(); int getIntValue(); void printImage();
void equalImage(); void addImage(int); void darkImage(int); void grayImage();
void gammaImage(); void reverseImage();


void main() {
	// 이미지 파일 --> 2차원 배열로 Loading
	loadImage();

	// 영상처리 알고리즘 구현
	// 밝게 하기 (=숫자 더하기)

	int value1 = getIntValue();
	printf("밝게 처리\n");
	addImage(value1);

	int value2 = getIntValue();
	printf("어둡게 처리\n");
	darkImage(value2);

	printf("흑백으로 처리\n");
	grayImage();

	printf("반전 처리\n");
	reverseImage();
}

///////////////
/// 함수 정의부
///////////////


// 공통 함수

void loadImage() {
	rfp = fopen(fileName, "rb");
	fread(inImage, sizeof(unsigned char), height * width, rfp);
	fclose(rfp);
	equalImage();
}

void printImage() {
	for (int i = height / 2 - 5; i < height / 2 + 5; i++) 
	{
		for (int k = width / 2 - 5 ; k < width / 2 + 5; k++) 
		{
			printf("%3d ", outImage[i][k]);
		}
		puts("");
	}
	puts("");
}

int getIntValue()
{
	int retValue;  // void로 하면 안되는 이유 int로 값을 받아서 메인함수에 돌려줘야돼서
	printf("정수값 --> ");
	scanf("%d", &retValue);

	return retValue;
}


// 영상처리 함수

void equalImage()  // 동일 영상 알고리즘
// 입력 배열을 출력 배열로!
{
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			outImage[i][k] = inImage[i][k];
		}
	}
	printImage();
}

void reverseImage() {
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = 255 - outImage[i][k];
		}
	}
	printImage();
}

void addImage(int val) {
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (outImage[i][k] + val < 255)
				outImage[i][k] += val;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();
}

void darkImage(int val)
{
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			if (inImage[i][k] - val >= 0)
				outImage[i][k] = inImage[i][k] - val;
			else
				outImage[i][k] = 0;
		}
	}
	printImage();
}

void grayImage()
{
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			if (inImage[i][k] < 127)
				outImage[i][k] = 0;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();
}