#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// (0) ������ ������ ���� ����
#define height 5
#define width 5

// (1) �޸�(2���� �迭 �غ�)
unsigned char image[height][width];

//�Լ� ����ο� ���Ǻ�
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
	// ���� �ʱ�ȭ
	srand((unsigned int)(time)(0)); // �ð� �ʱ�ȭ
	//�̹��� ���� --> 2���� �迭�� �ε�
	loadImage();
	// ���� ���
	printImage();
	// 3-1 ���� ���� ó��
	reverseImage();
	// 3-2 ���� ��� ó��
	int value;
	printf("����� �� --> ");
	scanf("%d", &value);
	addImage(value);
}