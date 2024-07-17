#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

////////////////////
///// ���� ������
////////////////////

FILE* rfp;
char fileName[200] = "D:/RAW/Etc_Raw(squre)/LENNA512.raw";
#define height 512
#define width 512

// �޸� Ȯ��
unsigned char inImage[height][width], outImage[height][width];


////////////////////
///// �Լ� �����
////////////////////
void loadImage(); int getIntValue(); void printImage();
void addImage(int); void equalImage(); 

void main()
{ //�̹��� ���Ͽ��� �޸𸮷� �ε�!
	loadImage(); //�Լ� ȣ��!

	// ����ó�� �˰��� ����
	// (1) ��� �ϱ� (= ���� ���ϱ�)
	int value = getIntValue();
	addImage(value);

}


////////////////////
///// �Լ� ���Ǻ�
////////////////////


/// ���� �Լ�

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
	printf("������ --> ");
	scanf("%d", &retValue);

	return retValue;

}


/// ����ó�� �Լ�
void equalImage()  // ���Ͽ��� �˰���
{  // �Է� �迭 --> ��� �迭
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			outImage[i][k] = inImage[i][k];
		}
	}
	printImage();
}

void addImage(int val)   // ���ϱ� �˰���
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