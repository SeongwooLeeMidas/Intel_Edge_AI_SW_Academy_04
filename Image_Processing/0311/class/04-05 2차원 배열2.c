#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#define height 3
#define width 5

void main()
{	//2���� �迭 
	//(0) �迭 �غ�
	int ary[height][width];

	// (1) �迭�� ���� �ҷ����� (���߿� �׸����� �о����)
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			ary[i][k] = 100;
		}
	}
	// (2) �迭�� ó���ϱ�(=Ȱ���ϱ�)
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			ary[i][k] += 10; // 10��ŭ ��� ó��!
		}
	}
	// (3) �迭 ����ϱ�(=������ ȭ�鿡 ���÷���)
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			printf("%3d ", ary[i][k]);
		}
		printf("\n");
	}
	// 5x7 ũ���� �迭 �غ��ϰ�, �迭�� 1,2,3 .. ���� ä���
	// �迭�� ���� ��� 2��� �ϰ�, �迭�� ����ϱ�
}

