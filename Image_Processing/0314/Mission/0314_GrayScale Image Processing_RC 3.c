#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> // GUI ���� ���
#include <math.h>

/////////////////////
// ���� ������
/////////////////////
HWND hwnd; // ���� ȭ��(�ܺ�, ������)
HDC hdc; // ���� ȭ�� (����, ����)

FILE* rfp, * wfp;
char fileName[200];
int inH, inW, outH, outW;
// �޸� Ȯ��
// unsigned char inImage[height][width], outImage[height][width];
unsigned char** inImage, ** outImage;


/////////////////////
// �Լ� �����
/////////////////////
void loadImage(); int getIntValue(); void printImage(); void printMenu();
void saveImage(); void freeInputMemory(); void freeOutputMemory();
void mallocInputMemory(); void mallocOutputMemory();

void equalImage(); void addImage(); void subImage(); void reverseImage();
void bwImage(); void zoomOut(); void zoomIn(); void zoomIn2();
void rotate(); void rotate2();
void shift();  void mirrorLR(); void mirrorXY();


void main() {
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(NULL);  // Windows 10 : hwnd

	char inKey = 0;
	while (inKey != '9') {
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
		case 'C': subImage(); break;
		case 'd':
		case 'D': reverseImage(); break;
		case 'e':
		case 'E': bwImage(); break;
		case 'f':
		case 'F': zoomOut(); break;
		case 'g':
		case 'G': zoomIn(); break;
		case 'h':
		case 'H': zoomIn2(); break;
		case 'i':
		case 'I': rotate(); break;
		case 'k': case 'K': rotate2(); break;
		case 'j': case 'J': shift(); break;
		case 'l': case 'L': mirrorLR(); break;
		case 'm': case 'M': mirrorXY(); break;
		}

	}

	freeInputMemory();
	freeOutputMemory();
}

/////////////////////
// �Լ� ���Ǻ�
/////////////////////
/// ���� �Լ�
//////////////
void printMenu() {
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("0.����  1.����  9. ����");
	puts("A.���� B.��� C.��Ӱ� D.���� E.��� F.��� G.Ȯ��(������) H.Ȯ��(�����) ~~~~");
	puts("I.ȸ�� K.ȸ��(�߾�,�����)");
	puts("L.�¿��Ī M.���ϴ�Ī");
}

void printImage() {
	system("cls");
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			int px = outImage[i][k];
			SetPixel(hdc, k + 50, i + 250, RGB(px, px, px));
		}
	}
}
void loadImage() {
	char fullName[200] = "C:/RAW/";

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

	// �޸� ����
	freeInputMemory();

	// �Է� ���� ����, �� ���ϱ�
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

	// printf("%d ", inImage[100][100]);

	equalImage();
}

void saveImage() {
	if (outImage == NULL)
		return;

	char fullName[200] = "C:/RAW/";
	char tmpName[50];
	printf("���ϸ�-->"); // out01, out02......
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");
	// �޸� --> ���� (���྿)
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	fclose(wfp);
	// MessageBox(hwnd, L"���� �Ϸ�", L"���� â", NULL);
	printf("���� �Ϸ�");
}
int getIntValue() {
	int retValue;
	printf("������-->"); scanf("%d", &retValue);
	return retValue;
}

void freeInputMemory() {
	if (inImage == NULL)
		return;
	for (int i = 0; i < inH; i++)
		free(inImage[i]); // �����ʿ� �ִ� 2���� �迭 ����
	free(inImage); // �װź��� ���ʿ� �ִ� 1���� �迭 ����
	inImage = NULL;
}

void freeOutputMemory() {
	if (outImage == NULL)
		return;
	for (int i = 0; i < outH; i++)
		free(outImage[i]); // �����ʿ� �ִ� 2���� �迭 ����
	free(outImage); // �װź��� ���ʿ� �ִ� 1���� �迭 ����
	outImage = NULL;
}

void mallocInputMemory() {
	inImage = (unsigned char**)malloc(sizeof(unsigned char*) * inH);
	for (int i = 0; i < inH; i++)
		inImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * inW);
}

void mallocOutputMemory() {
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * outH);
	for (int i = 0; i < inH; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * outW);

}


//////////////////
//  ����ó�� �Լ�
////////////////////
void equalImage() { // ���Ͽ��� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!!!) ��� �̹����� ũ�⸦ ���� -> �˰��� ����
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
	printImage();
}
void addImage() { // ���ϱ� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!!!) ��� �̹����� ũ�⸦ ���� -> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	int val = getIntValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] + val < 255)
				outImage[i][k] = inImage[i][k] + val;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();
}

void subImage() { // ���� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!!!) ��� �̹����� ũ�⸦ ���� -> �˰��� ����
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
	printImage();
}

void reverseImage() { // ���� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!!!) ��� �̹����� ũ�⸦ ���� -> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printImage();
}
void bwImage() { // ��� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!!!) ��� �̹����� ũ�⸦ ���� -> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] > 127)
				outImage[i][k] = 255;
			else
				outImage[i][k] = 0;
		}
	}
	printImage();
}

void zoomOut() { // ��� �˰���
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();
	// (�߿�!!!) ��� �̹����� ũ�⸦ ���� -> �˰��� ����
	outH = (int)(inH / scale);
	outW = (int)(inW / scale); // ���� �������� int �� �ᵵ �Ǵµ� int�� �Ἥ ������ ������ִ°� ���� �ڵ� �ۼ� ���
	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i / scale)][(int)(k / scale)] = inImage[i][k];
		}
	}
	printImage();
}

void zoomIn() { // Ȯ�� �˰���
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();
	// (�߿�!!!) ��� �̹����� ũ�⸦ ���� -> �˰��� ����
	outH = (int)(inH / scale);
	outW = (int)(inW / scale); // ���� �������� int �� �ᵵ �Ǵµ� int�� �Ἥ ������ ������ִ°� ���� �ڵ� �ۼ� ���
	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i * scale)][(int)(k * scale)] = inImage[i][k];
		}
	}
	printImage();
}

void zoomIn2() { // Ȯ�� �˰���
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();
	// (�߿�!!!) ��� �̹����� ũ�⸦ ���� -> �˰��� ����
	outH = (int)(inH / scale);
	outW = (int)(inW / scale); // ���� �������� int �� �ᵵ �Ǵµ� int�� �Ἥ ������ ������ִ°� ���� �ڵ� �ۼ� ���
	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			inImage[(int)(i / scale)][(int)(k / scale)] = outImage[i][k];
		}
	}
	printImage();
}

void rotate() { // ȸ�� �˰��� , ���� ������ �ȵ�� - �ٿ���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!!!) ��� �̹����� ũ�⸦ ���� -> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;

	// xd = cos*xs - sin*ys
	// yd = sin*xs + cos*ys , ��ǻ�� ������ degree ���� radian���� ó����


	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int xs = i;
			int ys = k; // �̷� ��ĵ� ������ ��������?
			int xd = (int)(cos(radian) * xs - sin(radian) * ys);
			int yd = (int)(sin(radian) * xs + cos(radian) * ys);

			// ȸ����Ų ��ġ�� ���̸� �����ߵ�
			if ((0 <= xd && xd < outH) && (0 <= yd && yd < outW))
				outImage[xd][yd] = inImage[xs][ys];
		}
	}
	printImage();
}

void rotate2() { // ȸ�� �˰��� , ���� ������ �ȵ�� - �ٿ���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!!!) ��� �̹����� ũ�⸦ ���� -> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;

	// xd = cos*xs - sin*ys
	// yd = sin*xs + cos*ys , ��ǻ�� ������ degree ���� radian���� ó����

	int cx = inH / 2; //center�� ���ؾߴ�
	int cy = inW / 2;

	for (int i = 0; i < outH; i++) { //������̶� in���� out
		for (int k = 0; k < outW; k++) {
			int xd = i;
			int yd = k; // �̷� ��ĵ� ������ ��������?
			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
			xs += cx;
			ys += cy;

			// ȸ����Ų ��ġ�� ���̸� �����ߵ�
			if ((0 <= xs && xs < outH) && (0 <= ys && ys < outW))
				outImage[xd][yd] = inImage[xs][ys];
		}
	}
	printImage();
}

void shift() { // �̵� �˰���
	int val = getIntValue();
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
			int new_i = i + val;
			int new_k = k + val;
			if (new_i >= 0 && new_i < outH && new_k >= 0 && new_k < outW)
				outImage[new_i][new_k] = inImage[i][k];
		}
	}
	printImage();
}

void mirrorLR() { //�¿��Ī
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
			outImage[i][outW - k - 1] = inImage[i][k];
		}
	}
	printImage();
}
void mirrorXY() { //���ϴ�Ī
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
			outImage[outH - i - 1][k] = inImage[i][k];
		}
	}
	printImage();
}