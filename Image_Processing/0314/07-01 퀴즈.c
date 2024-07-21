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
int inH, inW, outH, outW;
// �޸� Ȯ��
// unsigned char inImage[height][width], outImage[height][width];
unsigned char** inImage, ** outImage;

//////////////////
// �Լ� �����
//////////////////
void loadImage(); int getIntValue(); void printImage(); void printMenu(); void saveImage();
void freeInputMemory(); void freeOutputMemory();
void mallocInputMemory(); void mallocOutputMemory(); // �޸� �Ҵ�, ��� �̹����� �Ҵ�� �޸� ����

void equalImage(); void addImage(); void darkImage(); void grayImage();
void gammaImage(); void reverseImage(); void parabolCapImage(); // ���� ����, �Ķ� ĸ
void andImage(); void orImage(); void xorImage();


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
		//system("cls");

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
		case 'g':
		case 'G': parabolCapImage(); break;
		case 'h':
		case 'H': parabolCupImage(); break;
		case 'i':
		case 'I': andImage(); break;
		case 'j':
		case 'J': orImage(); break;
		case 'k':
		case 'K': xorImage(); break;
		}
	}

	freeInputMemory();
	freeOutputMemory();
}


//////////////////
// �Լ� ���Ǻ�
//////////////////
// ���� �Լ�
/////////////

void printMenu() { // �޴� �����
	puts("## GrayScale Image Processing (Beta 4) ##");
	puts("0.���� 1.����  9.����");
	puts("A.���� B.��� C.��Ӱ� D.���� E.��� F.���� G.�Ķ󺼶� CAP H.�Ķ󺼶� CUP I.AND ó�� J.OR ó�� H.XOR ó��");
}

void printImage() {
	system("cls");
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			int px = outImage[i][k];
			SetPixel(hdc, k + 50, i + 250, RGB(px, px, px)); // 
		}
	}
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

	// �޸� ����
	freeInputMemory();

	// ����, �� ���ϱ�
	inH = inW = (int)sqrt(fsize);

	// �޸� �Ҵ�
	mallocInputMemory();

	inImage = (unsigned char**)malloc(sizeof(unsigned char*) * inH);
	for (int i = 0; i < inH; i++)
		inImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * inW);

	// ���� --> �޸�

	rfp = fopen(fileName, "rb");
	for (int i = 0; i < inH; i++)
		fread(inImage[i], sizeof(unsigned char), inW, rfp);
	fclose(rfp);

	//printf("%d ", inImage[100][100]);

	equalImage();
}

void saveImage() {
	char fullName[200] = "D:/RAW/Etc_Raw(squre)//";
	char tmpName[50];
	printf("���ϸ�--> "); // out01, out02...
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, "_512.raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");
	// �޸� --> ���� (�� �྿)
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	fclose(wfp);
	//MessageBox(hwnd, L"���� �Ϸ�", L"���� â", NULL);
}

int getIntValue() {  // ���� ���� �Է¹����� int������, void ���� ���� ��ȯ ����
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
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * inH);
	for (int i = 0; i < inH; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * inW);

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
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
			if (inImage[i][k] - val >= 0

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

void parabolCapImage() { // �Ķ󺼶� Cap ó�� �˰���

	//�޸� �Ҵ�
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			outImage[i][k] = 255 - 255 * pow((inImage[i][k] / 128 - 1), 2);
		}
	}
	printf("�Ķ󺼶� CAP ó��\n");
	printImage();
}

void parabolCupImage() { // �Ķ󺼶� Cup ó�� �˰���

	//�޸� �Ҵ�
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			outImage[i][k] = 255 * pow((inImage[i][k] / 128 - 1), 2);
		}
	}
	printf("�Ķ󺼶� CUP ó��\n");
	printImage();
}

void andImage() { // And ó�� �˰���

	//�޸� �Ҵ�
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = inImage[i][k] & inImage[i][k];
		}
	}
	printf("And ó�� �˰���");
	printImage();
}

void orImage() { // Or ó�� �˰���

	// �޸� �Ҵ�
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = inImage[i][k] | inImage[i][k];

			// ��� ���� 255�� �ʰ��ϸ� 255�� ����
			if (outImage[i][k] > 255)
				outImage[i][k] = 255;
		}
	}
	printf("Or ó�� �˰���");
	printImage();
}

void xorImage() { // XOR ó�� �˰���

	// �޸� �Ҵ�
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = inImage[i][k] ^ inImage[i][k];

			// ��� ���� 255�� �ʰ��ϸ� 255�� ����
			if (outImage[i][k] > 255)
				outImage[i][k] = 255;
		}
	}
	printf("XOR ó�� �˰���");
	printImage();
}