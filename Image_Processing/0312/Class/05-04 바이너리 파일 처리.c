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


	// ���� ó�� 3�ܰ�
	// (1) ���� ����
	rfp = fopen(fileName, "rb");

	// (2) ���� �аų� ����
	// �� �濡 512x512 �о����
	fread(image, 1, height * width, rfp); //1����Ʈ�� �߶�

	// (3) ���� �ݱ�
	fclose(rfp);
	printf("%3d ", image[511][511]);
}