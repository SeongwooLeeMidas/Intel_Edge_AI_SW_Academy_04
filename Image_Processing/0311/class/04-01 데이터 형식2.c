#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	float fVal = 12345678901234567890.12345678901234567890;
	double dVal = 12345678901234567890.12345678901234567890;

	printf("%.20f \n", fVal);
	printf("%.20f \n", dVal);

	return 0;
}