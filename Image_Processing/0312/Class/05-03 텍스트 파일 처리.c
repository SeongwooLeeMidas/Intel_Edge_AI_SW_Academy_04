#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void main()
{
	char str[100]; //�о�� �� ��
	FILE* rfp;

	// ���� ó�� 3�ܰ�
	// (1) ���� ����
	rfp = fopen("c:\\windows\\win.ini", "rt");

	// (2) ���� �аų� ����
	int lineNum = 1;
	while (1) 
	{
		fgets(str, 100, rfp); //str�迭���� rfp �о�� �ִ� 100���ڷ�
		if (feof(rfp))
			break;
		printf("%2d�� : %s", lineNum, str);
		lineNum++;
	}

	// (3) ���� �ݱ�
	fclose(rfp);
}