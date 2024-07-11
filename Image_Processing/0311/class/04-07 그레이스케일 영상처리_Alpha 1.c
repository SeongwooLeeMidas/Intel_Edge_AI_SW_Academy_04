#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void main()
{
	srand((unsigned int)time(0)); //���� �ƴϰ� �ð� �ʱ�ȭ
	// (0) ������ ������ ũ�⸸ŭ �޸𸮸� Ȯ���ϴ� ��(jolly.raw: 10x10 �̹����� �����Ѵٸ�)
	#define height 10
	#define width 10

	// (1) 2���� �迭(=�޸�) �غ�
	unsigned char image[height][width];

	// (2) �̹��� ���� --> 2���� �迭�� �ε�(Loading)
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			image[i][k] = rand() % 256;
		}
	}

	// ���� �̹��� ���, �۾��� �� �Ѱ���. 
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			printf("%3d ", image[i][k]);
		}
		printf("\n");
	}

	// (3) ����ó�� ȿ�� (Image Processing)
	// (3-1) ����ϱ� �˰��� (50 ����)
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			if (image[i][k] + 50 < 256) //�Ϲ������� 8��Ʈ��, 256����
				image[i][k] += 50;
			else
				image[i][k] += 255;
		}
	}

	// (3-2) ��Ӱ� �˰��� (50 ����)
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			if(image[i][k] - 50 >0)
				image[i][k] -= 50;
			else
				image[i][k] = 0;

		}
	}

	// ��� �̹��� ���
	printf("\n");
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			printf("%3d ", image[i][k]);
		}
		printf("\n");
	}
}