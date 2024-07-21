#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void main()
{
	FILE* rfp;

	char fileName[200] = "D:/RAW/Etc_Raw(squre)/LENNA512.raw";
#define height 512
#define width 512

	unsigned char image[height][width];


	// 파일 처리 3단계
	// (1) 파일 열기
	rfp = fopen(fileName, "rb");

	// (2) 파일 읽거나 쓰기
	// 한 방에 512x512 읽어오기
	fread(image, 1, height * width, rfp); //1바이트로 잘라

	// (3) 파일 닫기
	fclose(rfp);
	printf("%3d ", image[511][511]);
}