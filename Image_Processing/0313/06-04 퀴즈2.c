#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> 

void main()
{
	double* p;
	double* q;

	p = (double*)malloc(sizeof(double) * 5);
	q = (double*)malloc(sizeof(double) * 5);

	double value = 0.1;
	for (int i = 0; i < 5; i++)
	{
		p[i] = value;
		value += 0.1;
	}

		for (int i = 0; i < 5; i++)
			q[5 - 1 - i] = p[i];

		printf("%lf, %lf, %lf", q[0], q[1], q[2]);
		
		free(p);
		free(q);
}