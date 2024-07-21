#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	char ch1 = 100;
	char ch2 = 'A';

	printf("%d %d \n", ch1, ch2);
	printf("%c %c \n", ch1, ch2);
	printf("%d \n", ch1 + ch2);
}