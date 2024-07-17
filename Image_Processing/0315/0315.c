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
int height;
int width;
// �޸� Ȯ��
// unsigned char inImage[height][width], outImage[height][width];
unsigned char** inImage = NULL, ** outImage = NULL;

//////////////////
// �Լ� �����
//////////////////
void loadImage(); int getIntValue(); void printImage(); void printMenu();
void saveImage(); void freeInputMemory(); void freeOutputMemory();
void mallocInputMemory(); void mallocOutputMemory();
double** mallocDoubleMemory(int, int); void freeDoubleMemory(double**, int);

void equalImage(); void addImage(); void darkImage(); void grayImage();
void gammaImage(); void reverseImage(); void parabolCapImage(); void parabolCupImage();
void andImage(); void orImage(); void xorImage(); void zoomOut(); void zoomIn();
void zoomIn2(); void rotate(); void rotate2(); void moveImage(); void histoStretch();
void endIn(); void histoEqual(); void mirrorImage(); void emboss(); void blur();
void sharp();



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
		case 'a': case 'A': equalImage(); break;
		case 'b': case 'B': addImage(); break;
		case 'c': case 'C': darkImage(); break;
		case 'd': case 'D': reverseImage(); break;
		case 'e': case 'E': grayImage(); break;
		case 'f': case 'F': gammaImage(); break;
		case 'g': case 'G': parabolCapImage(); break;
		case 'h': case 'H': parabolCupImage(); break;
		case 'i': case 'I': andImage(); break;
		case 'j': case 'J': orImage(); break;
		case 'k': case 'K': xorImage(); break;
		case 'l': case 'L': zoomOut(); break;
		case 'm': case 'M': zoomIn(); break;
		case 'n': case 'N': zoomIn2(); break;
		case 'q': case 'Q': rotate(); break;
		case 'r': case 'R': rotate2(); break;
		case 's': case 'S': moveImage(); break;
		case 'p': case 'P': histoStretch(); break;
		case 'o': case 'O': endIn(); break;
		case 'v': case 'V': histoEqual(); break;
		case 'u': case 'U': mirrorImage(); break;
		case 'x': case 'X': emboss(); break;
		case 'z': case 'Z': blur(); break;
		case 'w': case 'W': sharp(); break;
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
	puts("A.���� / B.��� / C.��Ӱ� / D.���� / E.��� / F.���� / G.�Ķ󺼶� CAP");
	puts("H.�Ķ󺼶� CUP / I.AND ó�� / J.OR ó�� / H.XOR ó�� / L.���");
	puts("M.Ȯ��(������) / N.Ȯ��(�����) / Q.ȸ�� / R.ȸ��(�߾�, �����)");
	puts("S.�̵� / P.������׷� ��Ʈ��Ī / O. ����-�� / V. ��Ȱȭ / U. ����");
	puts("X. ������ / Z. �� / W. ������");
}

void printImage() {
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			int px = outImage[i][k];
			SetPixel(hdc, k + 50, i + 250, RGB(px, px, px));
		}
	}
}

void loadImage() {
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("���ϸ�-->"); // flower512, LENA256
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	// (�߿�!) �̹����� ���� ���̸� ����
	rfp = fopen(fileName, "rb");
	fseek(rfp, 0L, SEEK_END); // ������ ������ �̵�
	long long fsize = ftell(rfp); // �� ���������?  262,144  --> 512
	fclose(rfp);
	//�޸� ����
	freeInputMemory();
	// �Է� ���� ����, �� ���ϱ�
	inH = inW = (int)sqrt(fsize);
	// �޸� �Ҵ�
	mallocInputMemory();

	// ���� --> �޸�
	rfp = fopen(fileName, "rb");
	for (int i = 0; i < inH; i++)
		fread(inImage[i], sizeof(unsigned char), inW, rfp);
	fclose(rfp);

	// printf("%d ", inImage[100][100]);

	equalImage();
}


void saveImage() {
	if (outImage == NULL)
		return;
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("���ϸ�--> "); // out01, out02...
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");
	// �޸� --> ���� (�� �྿)
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	fclose(wfp);
	MessageBox(hwnd, L"���� �Ϸ�", L"���� â", NULL);
}

int getIntValue() {
	int retValue;
	printf("���� ��--> ");
	scanf("%d", &retValue);
	return retValue;
}

void freeInputMemory() {
	if (inImage == NULL)
		return;
	for (int i = 0; i < inH; i++)
		free(inImage[i]);
	free(inImage);
	inImage = NULL;
}
void mallocInputMemory() {
	inImage = (unsigned char**)malloc(sizeof(unsigned char*) * inH);
	for (int i = 0; i < inH; i++)
		inImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * inW);
}
void freeOutputMemory() {
	if (outImage == NULL)
		return;
	for (int i = 0; i < outH; i++)

		free(outImage[i]);
	free(outImage);
	outImage = NULL;
}
void mallocOutputMemory() {
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * outH);
	for (int i = 0; i < outH; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * outW);
}

double** mallocDoubleMemory(int h, int w) {
	double** retMemory;
	retMemory = (double**)malloc(sizeof(double*) * h);
	for (int i = 0; i < h; i++)
		retMemory[i] = (double*)malloc(sizeof(double) * w);
	return retMemory;
}

void freeDoubleMemory(double** memory, int h) {
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		free(memory[i]);
	free(memory);
	memory = NULL;
}

/////////////////
// ���� ó�� �Լ�
/////////////////

void equalImage() { // ���Ͽ��� �˰���

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

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

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	int val = getIntValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
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

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	int val = getIntValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] - val > 0)
				outImage[i][k] = inImage[i][k] - val;
			else
				outImage[i][k] = 0;
		}
	}
	printf("��Ӱ� ó��\n");
	printImage();
}

void grayImage() { // ��� ó�� �˰���

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
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

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printf("���� ó��\n");
	printImage();
}

void gammaImage() { // ���� ó�� �˰���

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	float gamma;
	printf("���� ó�� (0~10) --> ");
	scanf("%f", &gamma); // ���� ���� �Է� ����

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
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

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++)
	{
		for (int k = 0; k < inW; k++)
		{
			outImage[i][k] = 255 - 255 * pow((inImage[i][k] / 128 - 1), 2);
		}
	}
	printf("�Ķ󺼶� CAP ó��\n");
	printImage();
}

void parabolCupImage() { // �Ķ󺼶� Cup ó�� �˰���

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++)
	{
		for (int k = 0; k < inW; k++)
		{
			outImage[i][k] = 255 * pow((inImage[i][k] / 128 - 1), 2);
		}
	}
	printf("�Ķ󺼶� CUP ó��\n");
	printImage();
}

void andImage() { // And ó�� �˰���

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][k] & inImage[i][k];
		}
	}
	printf("And ó�� �˰���");
	printImage();
}

void orImage() { // Or ó�� �˰���

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
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

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			outImage[i][k] = inImage[i][k] ^ inImage[i][k];

			// ��� ���� 255�� �ʰ��ϸ� 255�� ����
			if (outImage[i][k] > 255)
				outImage[i][k] = 255;
		}
	}
	printf("XOR ó�� �˰���");
	printImage();
}

void zoomOut() { // ��� �˰���
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = (int)(inH / scale);
	outW = (int)(inW / scale);

	// �޸� �Ҵ�
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i / scale)][(int)(k / scale)] = inImage[i][k];
		}
	}
	printf("���");
	printImage();
}

void zoomIn() { // ������ Ȯ�� �˰���
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = (int)(inH * scale);
	outW = (int)(inW * scale);

	// �޸� �Ҵ�
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i * scale)][(int)(k * scale)] = inImage[i][k];
		}
	}
	printf("Ȯ��");
	printImage();
}

void zoomIn2() { // ����� Ȯ�� �˰���
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = (int)(inH * scale);
	outW = (int)(inW * scale);

	// �޸� �Ҵ�
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = inImage[(int)(i / scale)][(int)(k / scale)];
		}
	}
	printf("Ȯ��");
	printImage();
}
void rotate() { // ȸ�� �˰���

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();
	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;
	// xd = cos(xs) - sin(ys)
	// yd = sin(xs) + cos(ys)

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int xs = i;
			int ys = k;
			int xd = cos(radian) * xs - sin(radian) * ys;
			int yd = sin(radian) * xs + cos(radian) * ys;

			if ((0 <= xd && xd < outH) && (0 <= yd && yd < outW))
				outImage[xd][yd] = inImage[xs][ys];
		}
	}
	printf("ȸ��\n");
	printImage();
}

void rotate2() { // ȸ��(�߾�, �����) �˰���

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;
	// xd = cos(xs) - sin(ys)
	// yd = sin(xs) + cos(ys)

	int cx = inH / 2;
	int cy = inW / 2;
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			int xd = i;
			int yd = k;
			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
			xs += cx;
			ys += cy;
			if ((0 <= xs && xs < outH) && (0 <= ys && ys < outW))
				outImage[xd][yd] = inImage[xs][ys];
		}
	}
	printf("ȸ�� �����\n");
	printImage();
}

void histoStretch() { // ������׷� ��Ʈ��Ī �˰���

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// ���⼭���� ����ó�� �˰��� ����~~
	// new = (old - low) / (high - low) * 255.0
	int high = inImage[0][0], low = inImage[0][0];
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k] < low;
			if (inImage[i][k] > high)
				high = inImage[i][k];
		}
	}
	int old, new;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			old = inImage[i][k];
			new = (int)((double)(old - low) / (double)(high - low) * 255.0);
			if (new > 255)
				new = 255;
			if (new < 0)
				new = 0;
			outImage[i][k] = new;
		}
	}
	printf("������׷� ��Ʈ��Ī\n");
	printImage();
}

void endIn() { // ������ Ž�� �˰���

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// ���⼭���� ����ó�� �˰��� ����~~
	// new = (old - low) / (high - low) * 255.0
	int high = inImage[0][0], low = inImage[0][0];
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k] < low;
			if (inImage[i][k] > high)
				high = inImage[i][k];
		}
	}

	high -= 50;
	low += 50;

	int old, new;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			old = inImage[i][k];
			new = (int)((double)(old - low) / (double)(high - low) * 255.0);
			if (new > 255)
				new = 255;
			if (new < 0)
				new = 0;
			outImage[i][k] = new;
		}
	}
	printf("����-��\n");
	printImage();
}

void histoEqual() { // ������׷� ��Ȱȭ �˰���

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();


	// 1�ܰ� : �󵵼� ���� (=������׷�)
	int histo[256] = { 0. };
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			histo[inImage[i][k]]++;

	// 2�ܰ� : ���� ������׷� ����
	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];
	for (int i = 1; i < 256; i++)
		sumHisto[i] = sumHisto[i - 1] + histo[i];


	// 3�ܰ� : ����ȭ�� ������׷� ���� normalHisto = sumHisto * (1.0 / (inH*inW) * 255.0;
	double normalHisto[256] = { 1.0, };
	for (int i = 0; i < 256; i++) {
		normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0;
	}
	// 4�ܰ� : inImage�� ����ȭ�� ������ ġȯ
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = (unsigned char)normalHisto[inImage[i][k]];
		}
	}
	printf("������׷� ��Ȱȭ\n");
	printImage();
}
void moveImage() { // �̹��� �̵� �˰���
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	int a = getIntValue();
	int b = getIntValue();
	int i, k = 0;
	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			// �̹��� �̵� �� ��踦 ����� ��츦 ����Ͽ� �ε����� üũ�Ͽ� ó��
			if (i + a >= 0 && i + a < inH && k - b >= 0 && k - b < inW) {
				outImage[i][k] = inImage[i + a][k - b];
			}
			else {
				outImage[i][k] = 0; // ��踦 ����� ��쿡�� 0���� ó���ϰų� �ٸ� ������� ó��
			}
		}
	}
	printf("�̹��� �̵�\n");
	printImage();
}

void mirrorImage() {
	printf("1 = ���� ���� or 2 = �¿� ����\n");
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	int a = getIntValue();
	// 1�϶��� �¿�, 2�϶��� ���� ����

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (a == 1)
				outImage[i][k] = inImage[inW - 1 - i][k];
			else
				outImage[i][k] = inImage[i][inH - 1 - k];
		}
	}
	printf("���� \n");
	printImage();
}

void emboss() { // ȭ�ҿ��� ó�� : ������ �˰���

	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {-1.0, 0.0, 0.0}, // ������ ����ũ
						  { 0.0, 0.0, 0.0},
						  { 0.0, 0.0, 1.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++) // 2 ��� 1���� ���ص� �Ǳ� ��
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInImage[i + m][k + n] * mask[m][n];
				}
				tmpOutImage[i][k] = S;
			}
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void blur() { // ȭ�ҿ��� ó�� : ���� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {1. / 9, 1. / 9, 1. / 9}, // ���� ����ũ
						  {1. / 9, 1. / 9, 1. / 9},
						  {1. / 9, 1. / 9, 1. / 9} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}
void sharp() { // ȭ�ҿ��� ó�� : ������ �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {0.0, -1.0 ,0.0}, // ������ ����ũ
						  {-1.0 ,5.0, -1.0},
						  {0.0, -1.0, 0.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}