#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

//int main(void)
//{
//	// 5��¥�� �迭�� �غ��ϰ�, ���� 100���� 104���� ����
//
//	const int SIZE = 5;
//
//	int ary[5];
//	int num = 100;
//
//	for (int i = 0; i < 5; i++)
//	{
//		ary[i] = num;
//		num++;
//	}
//
//	return 0;
//
//	// ����: �迭 10���� �غ��ϰ�, 5���� 5�� ����� ����, �׸��� �迭�� �հ�
//} 

void main()
{
	int ary[10];
	int num = 5;

	for (int i = 0; i < 10; i++)
	{
		ary[i] = num;
		num += 5;
	}

	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		sum += ary[i];
	}

	printf("���� %d �Դϴ�.\n", sum);
} 

//10���� 9���� �� ������ �����. ���� �⺻���� ����.
// ����: �迭 20�� �غ��ϰ� 2���� �Ҽ��� 20�� ����. �׸��� �迭 ���� ���.


