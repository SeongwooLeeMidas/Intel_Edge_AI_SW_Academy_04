#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> // GUI ���� ���

/////////////////////
// ���� ������
/////////////////////
HWND hwnd; // ���� ȭ��(�ܺ�, ������)
HDC hdc; // ���� ȭ�� (����, ����)

FILE* rfp, * wfp;
char fileName[200];
#define height 512
#define width 512
// �޸� Ȯ��
unsigned char inImage[height][width], outImage[height][width];

/////////////////////
// �Լ� �����
/////////////////////
void loadImage(); int getIntValue(); void printImage(); void printMenu();
void saveImage();
void equalImage(); void addImage(); void subImage(); void reverseImage();
void bwImage();


void main() {
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(NULL);  // Windows 10 : hwnd

	char inKey = 0;
	while (inKey != '9') {
		printMenu();
		inKey = _getch();
		system("cls");
		switch (inKey)
		{
		case '0': loadImage(); break;
		case '1': saveImage(); break;
		case '9': break;
		case 'a':
		case 'A': equalImage(); break;
		case 'b':
		case 'B': addImage(); break;
		case 'c':
		case 'C': subImage(); break;
		case 'd':
		case 'D': reverseImage(); break;
		case 'e':
		case 'E': bwImage(); break;
		}

	}

}

/////////////////////
// �Լ� ���Ǻ�
/////////////////////
/// ���� �Լ�
//////////////
void printMenu() {
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("0.����  1.����  9. ����");
	puts("A.���� B.��� C.��Ӱ� D.���� E.��� ~~~~");
}

void printImage() {
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			int px = outImage[i][k];
			SetPixel(hdc, k + 50, i + 250, RGB(px, px, px));
		}
		printf("\n");
	}
	printf("\n");
}
void loadImage() {
	char fullName[200] = "D:/RAW/Pet_RAW(squre)/Pet_RAW(512x512)/";
	char tmpName[50];
	printf("���ϸ�-->"); // cat01, dog05
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, "_512.raw");
	strcpy(fileName, fullName);

	rfp = fopen(fileName, "rb");
	fread(inImage, sizeof(unsigned char), height * width, rfp);
	fclose(rfp);
	equalImage();
}

void saveImage() {
	char fullName[200] = "D:/RAW/Pet_RAW(squre)/Pet_RAW(512x512)/";
	char tmpName[50];
	printf("���ϸ�-->"); // out01, out02......
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, "_512.raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");
	// �޸� --> ���� (���྿)
	for (int i = 0; i < height; i++)
		fwrite(outImage[i], sizeof(unsigned char), width, wfp);
	fclose(wfp);
	// MessageBox(hwnd, L"���� �Ϸ�", L"���� â", NULL);
	printf("���� �Ϸ�");
}

int getIntValue() {
	int retValue;
	printf("������-->"); scanf("%d", &retValue);
	return retValue;
}
//////////////////
//  ����ó�� �Լ�
////////////////////
void equalImage() { // ���Ͽ��� �˰���
	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	printImage();
}
void addImage() { // ���ϱ� �˰���
	// �Է� �迭 --> ��� �迭
	int val = getIntValue();
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (inImage[i][k] + val < 255)
				outImage[i][k] = inImage[i][k] + val;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();
}

void subImage() { // ���� �˰���
	// �Է� �迭 --> ��� �迭
	int val = getIntValue();
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (inImage[i][k] - val > 0)
				outImage[i][k] = inImage[i][k] - val;
			else
				outImage[i][k] = 0;
		}
	}
	printImage();
}

void reverseImage() { // ���� �˰���
	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printImage();
}

void bwImage() { // ��� �˰���
	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (inImage[i][k] > 127)
				outImage[i][k] = 255;
			else
				outImage[i][k] = 0;
		}
	}
	printImage();
}