#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> 

void main()
{
	/*int size;
	size = 50;
	unsigned char ary[size];*/

	int size = 50;
	int* p; // �ּҴ� �˾ƾ���!!
	(int*) malloc(4*50); //50ĭ�� ���� ������ int������(4����Ʈ) �߶�! �׷��� 4x50��

	//*(p + 0) = 100; //p�� ������ 100
	//*(p + 1) = 101;
	//*(p + 2) = 102;
	p[0] = 100;
	p[1] = 200;
	p[2] = 300;

	printf("%d %d \n", *(p + 1), p[1]);

	free(p);

	// ���� : ������ ���� �޸� 100ĭ Ȯ�� ��, �ű⿡ 1234, 1235 ... ���� �����ϱ�
	// �׸��� �հ� ���
	
	int SIZE = 100;
	int* p;
	p = (int*) malloc(sizeof(int) * SIZE);
	int num = 1234;
	for (int i = 0; i < SIZE; i++) {
		// *(p + i) = num;
		p[i] = num;
		num++;
	}
	long long hap=0;
	for (int i = 0; i < SIZE; i++)
		hap += p[i];
	printf("%ld ", hap);
	free(p);

	// ���� : �Ǽ��� ���� �޸� 5ĭ¥���� 2�� �غ��ϰ�, ù ��°���� 0.1 ~ 0.5���� ����,
	// �� ��°���� ù ��°�� �������� ����.

// ����: �Ǽ��� ���� �޸� 5ĭ¥���� 2�� �غ��ϰ�, ù��°���� 0.1 ~0.5���� ����,
//			�ι�°���� ù��°�� �������� ����.
	double* p;
	double* q;

	p = (double*)malloc(sizeof(double) * 5);
	q = (double*)malloc(sizeof(double) * 5);

	double value = 0.1;
	for (int i = 0; i < 5; i++) {
		p[i] = value;
		value += 0.1;
	}
	for (int i = 0; i < 5; i++)
		q[5 - 1 - i] = p[i];		// �� �迭�� ũ��� ���� ���ҵ��� �ݴ� ������ ������ �� ����

	printf("%lf, %lf, %lf", q[0], q[1], q[2]);

	free(p);
	free(q);


}