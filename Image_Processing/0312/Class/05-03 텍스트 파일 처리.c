#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void main()
{
	char str[100]; //읽어올 한 줄
	FILE* rfp;

	// 파일 처리 3단계
	// (1) 파일 열기
	rfp = fopen("c:\\windows\\win.ini", "rt");

	// (2) 파일 읽거나 쓰기
	int lineNum = 1;
	while (1) 
	{
		fgets(str, 100, rfp); //str배열에다 rfp 읽어와 최대 100글자로
		if (feof(rfp))
			break;
		printf("%2d행 : %s", lineNum, str);
		lineNum++;
	}

	// (3) 파일 닫기
	fclose(rfp);
}