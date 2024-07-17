#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

//////////////
// ���� ������
//////////////

FILE* rfp;
char fileName[200] = "D:/RAW/Etc_Raw(squre)/LENNA512.raw";
#define height 512
#define width 512

// �޸� Ȯ��
unsigned char inImage[height][width], outImage[height][width];


////////////////
// �Լ��� �����
//////////////// 
void loadImage(); int getIntValue(); void printImage();
void equalImage(); void addImage(int); void darkImage(int); void grayImage();
void gammaImage(); void reverseImage();


void main() {
	// �̹��� ���� --> 2���� �迭�� Loading
	loadImage();

	// ����ó�� �˰��� ����
	// ��� �ϱ� (=���� ���ϱ�)

	int value1 = getIntValue();
	printf("��� ó��\n");
	addImage(value1);

	int value2 = getIntValue();
	printf("��Ӱ� ó��\n");
	darkImage(value2);

	printf("������� ó��\n");
	grayImage();

	printf("���� ó��\n");
	reverseImage();
}

///////////////
/// �Լ� ���Ǻ�
///////////////


// ���� �Լ�

void loadImage() {
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
	printf("������ --> ");
	scanf("%d", &retValue);

	return retValue;
}


// ����ó�� �Լ�

void equalImage()  // ���� ���� �˰���
// �Է� �迭�� ��� �迭��!
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