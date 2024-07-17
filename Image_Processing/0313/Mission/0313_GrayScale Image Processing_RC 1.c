#define _CRT_SECURE_NO_WARNINGS // scanf_s �Ⱦ�����
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <Windows.h> // GUI ���� ���

//////////////////
// ���� ������
//////////////////
HWND hwnd; // ������ ȭ��(�ܺ�, ������)
HDC hdc; // ������ ȭ��(����, ����)

FILE* rfp, * wfp;
char fileName[200];
int height;
int width;
// �޸� Ȯ��
// unsigned char inImage[height][width], outImage[height][width];
unsigned char** inImage, ** outImage;

//////////////////
// �Լ� �����
//////////////////
void loadImage(); int getIntValue(); void printImage(); void printMenu(); void saveImage();

void equalImage(); void addImage(); void darkImage(); void grayImage();
void gammaImage(); void reverseImage(); void parabolImage();




//////////////////
// ���� �Լ���
//////////////////

void main() {
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(NULL); // Windows 10 : hwnd, Windows 11 : NULL

	char inKey = 0;
	while (inKey != '9') { // �޴� ȣ��
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
		case 'C': darkImage(); break;
		case 'd':
		case 'D': reverseImage(); break;
		case 'e':
		case 'E': grayImage(); break;
		case 'f':
		case 'F': gammaImage(); break;
			/*case 'g':
			case 'G': parabolImage(); break;*/
		}
	}
	for (int i = 0; i < height; i++)
		free(inImage[i]);
	free(inImage);
}




//	// �̹��� ���� --> �޸𸮷� �ε�
//	loadImage();
//
//	// ����ó�� �˰��� ����
//	// (1) ����ϱ� (= ���� ���ϱ�)
//
//	int value1 = getIntValue();
//	printf("��� ó��\n");
//	addImage(value1);
//
//	int value2 = getIntValue();
//	printf("��Ӱ� ó��\n");
//	darkImage(value2);
//
//	printf("��� ó��\n");
//	grayImage();
//
//	printf("���� ó��\n");
//	reverseImage();
//
//	float gamma;
//	printf("���� ó�� (0~10) --> ");
//	scanf("%f", &gamma);
//	printf("\n���� ó�� ��� \n");
//	gammaImage(gamma);
//
//	float c;
//	printf("�Ķ󺼶� ó�� (���� ��) --> ");
//	scanf("%f", &gamma);
//	printf("�Ķ󺼶� ó�� (�����ϸ� ��� ��) --> ");
//	scanf("%f", &c);
//	parabolImage(gamma, c);
//}




//////////////////
// �Լ� ���Ǻ�
//////////////////
// ���� �Լ�
/////////////

void printMenu() { // �޴� �����
	puts("## GrayScale Image Processing (Beta 4) ##");
	puts("0.���� 1.����  9.����");
	puts("A.���� B.��� C.��Ӱ� D.���� E.��� F.���� G.�Ķ󺼶�");
}

void printImage() {
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			int px = outImage[i][k];
			SetPixel(hdc, k + 50, i + 250, RGB(px, px, px)); // 
		}
		printf("\n");
	}
	printf("\n");

	// �޸� �Ҵ� ����

	for (int i = 0; i < height; i++)
		free(outImage[i]);
	free(outImage);
}

void loadImage() {
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("���ϸ�--> "); // flower512, LENA256
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	// (�߿�!) �̹����� ���� ���̸� ����
	rfp = fopen(fileName, "rb");
	fseek(rfp, 0L, SEEK_END); // ������ ������ �̵�
	long long fsize = ftell(rfp); // �� ���������? 262,144 --> 512
	fclose(rfp);
	// ����, �� ���ϱ�
	height = width = (int)sqrt(fsize);

	// �޸� �Ҵ�
	inImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		inImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	// ���� --> �޸�

	rfp = fopen(fileName, "rb");
	for (int i = 0; i < height; i++)
		fread(inImage[i], sizeof(unsigned char), width, rfp);
	fclose(rfp);

	//printf("%d ", inImage[100][100]);

	equalImage();
}

void saveImage() {
	char fullName[200] = "D:/RAW/Pet_RAW(squre)/Pet_RAW(512x512)/";
	char tmpName[50];
	printf("���ϸ�--> "); // out01, out02...
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, "_512.raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");
	// �޸� --> ���� (�� �྿)
	for (int i = 0; i < height; i++)
		fwrite(outImage[i], sizeof(unsigned char), width, wfp);
	fclose(wfp);
	MessageBox(hwnd, L"���� �Ϸ�", L"���� â", NULL);
}

int getIntValue() {
	int retValue;
	printf("���� ��--> ");
	scanf("%d", &retValue);
	return retValue;
}



/////////////////
// ���� ó�� �Լ�
/////////////////

void equalImage() { // ���Ͽ��� �˰���

	// �޸� �Ҵ�
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	printf("���� �̹��� ����\n");
	printImage();
}

void addImage() { // ���ϱ�(���) �˰���

	// �޸� �Ҵ�
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	int val = getIntValue();
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (inImage[i][k] + val < 255)
				outImage[i][k] = inImage[i][k] + val;
			else
				outImage[i][k] = 255;
		}
	}
	printf("��� ó��\n");
	printImage();
}
void darkImage() { // ��Ӱ� �˰���

	// �޸� �Ҵ�
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	int val = getIntValue();
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (inImage[i][k] - val >= 0)
				outImage[i][k] = inImage[i][k] - val;
			else
				outImage[i][k] = 0;
		}
	}
	printf("��Ӱ� ó��\n");
	printImage();
}

void grayImage() { // ��� ó�� �˰���

	// �޸� �Ҵ�
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char**)malloc(sizeof(unsigned char*) * width);

	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (inImage[i][k] < 127)
				outImage[i][k] = 0;
			else
				outImage[i][k] = 255;
		}
	}
	printf("��� ó��\n");
	printImage();
}

void reverseImage() { // ���� �˰���

	//
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printf("���� ó��\n");
	printImage();
}

void gammaImage() { // ���� ó�� �˰���

	// �޸� �Ҵ�
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char**)malloc(sizeof(unsigned char*) * width);

	float gamma;
	printf("���� ó�� (0~10) --> ");
	scanf("%f", &gamma); // ���� ���� �Է� ����

	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			//�ȼ� �� 0~1�� ����ȭ
			float normalized_pixel = (float)inImage[i][k] / 255.0;
			//���� �Լ� ������ ������ �� ���
			float corrected_pixel = pow(normalized_pixel, gamma);

			corrected_pixel *= 255.0;

			if (corrected_pixel < 0)
				corrected_pixel = 0;
			if (corrected_pixel > 255)
				corrected_pixel = 255;

			outImage[i][k] = (unsigned char)corrected_pixel;
		}
	}
	printf("���� ó��\n");
	printImage();
}

//void parabolimage(float gamma, float c) { // �Ķ󺼶� ó�� �˰��� (����� ��.. ����..�ƿ�)
//	float resultValue = 0;
//	printf("���� ó�� (0~10) --> ");
//	scanf("%f", &gamma); // ���� ���� �Է� ����
//	printf("�Ķ󺼶� ó�� (�����ϸ� ��� ��) --> ");
//	scanf("%f", &c);
//	for (int i = 0; i < height; i++) {
//		for (int k = 0; k < width; k++) {
//			//�ȼ� �� 0~1�� ����ȭ
//			float normalizedPixel = (float)inImage[i][k] / 255.0;
//
//			if (inImage[i][k] > 127)
//				// cap �Ķ󺼶� ���� - ���� ���� ��ü������
//				resultValue = 255.0 - 225.0 * pow(inImage[i][k] / 128.0 - 1.0, 2);
//			else // inimage[i][k] <= 127 ������ ����Ͽ� else ����� ����
//				resultValue = 225.0 * pow(inImage[i][k] / 128.0 - 1.0, 2);
//
//
//			if (resultValue < 0)
//				resultValue = 0;
//			if (resultValue > 255)
//				resultValue = 255;
//
//
//
//			outImage[i][k] = (unsigned char)resultValue;
//		}
//	}
//	printf("�Ķ󺼶� ó��\n");
//	printImage();
//}