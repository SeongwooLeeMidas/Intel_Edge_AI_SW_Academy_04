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
void equalImage(); void addImage(); void subImage(); void darkImage(); void grayImage();
void bwImage(); void reverseImage(); 


void main() {

	char inKey = 0;
	while (inKey != 9) {
		printMenu();
		inKey = _getch();
		system("cls");

		switch (inKey)
		{
		case '0': loadImage();
			break;

		case'9':
			break;

		case 'a':
		case'A': equalImage();
			break;

		case'b':
		case'B': addImage();
			break;

		case 'c':
		case 'C': subImage();
			break;

		case 'd':
		case 'D': reverseImage();
			break;

		case 'e':
		case 'E': bwImage();
			break;
		}

	}
}


///////////////
/// 함수 정의부
///////////////


// 공통 함수
void printMenu()
{
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts(" 0.열기  1.저장  9.종료");
	puts(" A.동일  B.밝게  C.어둡게  D.반전  E.흑백");
}


void loadImage() {
	char fullName[200] = "D:/RAW/Pet_RAW(squre)/Pet_RAW(512x512)/";
	char tmpName[50];

	printf("파일명 --> ");
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, "_512.raw");
	strcpy(fileName, fullName);

	rfp = fopen(fileName, "rb");
	fread(inImage, sizeof(unsigned char), height * width, rfp);
	fclose(rfp);
	equalImage();
}

void printImage() {
	for (int i = height / 2 - 5; i < height / 2 + 5; i++)
	{
		for (int k = width / 2 - 5; k < width / 2 + 5; k++)
		{
			printf("%3d ", outImage[i][k]);
		}
		puts("");
	}
	puts("");
}

int getIntValue()
{
	int retValue;
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

void addImage() {
	int val = getIntValue();
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

void subImage()
{
	int val = getIntValue();
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (inImage[i][k] - val > 0)
				outImage[i][k] = inImage[i][k] - val;
			else
				outImage[i][k] = 0;
		}
	}
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