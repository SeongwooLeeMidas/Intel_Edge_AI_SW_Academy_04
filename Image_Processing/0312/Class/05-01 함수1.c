#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void main() 
{
	int num1 = 100;
	int num2 = 200;
	int sum;

	sum = num1 + num2;

	printf("%d \n", sum);
}

int plusNumber(int n1, int n2)
{
	int retValue;
	retValue = n1 + n2;
	return retValue;


}