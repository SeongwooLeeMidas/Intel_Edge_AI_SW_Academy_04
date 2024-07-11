#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void main()
{
	srand((unsigned int)time(0)); //�ð� �ʱ�ȭ

	// ������ ������ ũ�⸸ŭ �޸� Ȯ�� �۾�
#define height 7
#define width 7

// 2���� �迭 �غ�, �޸� �Ҵ�
	unsigned char image[height][width];

	// �̹��� ������ 2���� �迭�� �ε�
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			image[i][k] = rand() % 256;
		}
	}

	// ���� ���
	printf("���� �̹����� ����մϴ�.\n");
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			printf("%3d ", image[i][k]);
		}
		puts("");
	}

	// �̹����� �����ؼ� ���
	printf("\n�̹����� �����ؼ� ����մϴ�.\n");
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			image[i][k] = 255 - image[i][k];
		}		
	}

	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			printf("%3d ", image[i][k]);
		}
		puts("");
	}


	// ����ó�� ȿ�� (���ó��, 0�� 255�� ����)
	printf("\n������� ó���Ͽ� ����մϴ�.\n");
	
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			if (image[i][k] - 127 >= 0)
				image[i][k] = 0;
			else
				image[i][k] = 255;
		}
	}

	// ��� �̹��� ���	
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			printf("%3d ", image[i][k]);
		}
		puts("");
	}
}