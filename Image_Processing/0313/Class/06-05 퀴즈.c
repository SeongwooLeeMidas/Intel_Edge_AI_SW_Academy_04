#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> 

void main()
{
	unsigned char height = 512;
	unsigned char width = 512;

	char** p;
	p = (unsigned char**)malloc(sizeof(unsigned char*) * height);

	int value = 1;
	for (int i = 0; i < height / 2; i++)
	{
		for (int k = 0; k < width; k++)
		{
			printf("%c ", p[i][k]);
		}
		puts("");
	}

	for (int i = 0; i < width; i++)
		free(p[i]);
	free(p);
}