#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> // GUI 지원 기능
#include <math.h>

/////////////////////
// 전역 변수부
/////////////////////
HWND hwnd; // 윈도 화면(외부, 물리적)
HDC hdc; // 윈도 화면 (내부, 논리적)

FILE* rfp, * wfp;
char fileName[200];
int height;
int width;
// 메모리 확보
// unsigned char inImage[height][width], outImage[height][width];
unsigned char** inImage, ** outImage;


/////////////////////
// 함수 선언부
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
	for (int i = 0; i < height; i++)
		free(inImage[i]);
	free(inImage);

}

/////////////////////
// 함수 정의부
/////////////////////
/// 공통 함수
//////////////
void printMenu() {
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("0.열기  1.저장  9. 종료");
	puts("A.동일 B.밝게 C.어둡게 D.반전 E.흑백 ~~~~");
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

	for (int i = 0; i < height; i++)
		free(outImage[i]);
	free(outImage);
}
void loadImage() {
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("파일명-->"); // flower512, LENA256
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	// (중요!) 이미지의 폭과 높이를 결정
	rfp = fopen(fileName, "rb");
	fseek(rfp, 0L, SEEK_END); // 파일의 끝으로 이동
	long long fsize = ftell(rfp); // 나 어디쯤이지?  262,144  --> 512
	fclose(rfp);
	// 높이, 폭 구하기
	height = width = (int)sqrt(fsize);
	// 메모리 할당
	inImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		inImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	// 파일 --> 메모리
	rfp = fopen(fileName, "rb");
	for (int i = 0; i < height; i++)
		fread(inImage[i], sizeof(unsigned char), width, rfp);
	fclose(rfp);

	// printf("%d ", inImage[100][100]);

	equalImage();
}

void saveImage() {
	char fullName[200] = "D:/RAW/Pet_RAW(squre)/Pet_RAW(512x512)/";
	char tmpName[50];
	printf("파일명-->"); // out01, out02......
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, "_512.raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");
	// 메모리 --> 파일 (한행씩)
	for (int i = 0; i < height; i++)
		fwrite(outImage[i], sizeof(unsigned char), width, wfp);
	fclose(wfp);
	// MessageBox(hwnd, L"저장 완료", L"저장 창", NULL);
	printf("저장 완료");
}

int getIntValue() {
	int retValue;
	printf("정수값-->"); scanf("%d", &retValue);
	return retValue;
}
//////////////////
//  영상처리 함수
////////////////////
void equalImage() { // 동일영상 알고리즘

	// 메모리 할당
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	printImage();
}
void addImage() { // 더하기 알고리즘
	// 메모리 할당
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	// 입력 배열 --> 출력 배열
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

void subImage() { // 빼기 알고리즘
	// 메모리 할당
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);
	// 입력 배열 --> 출력 배열
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

void reverseImage() { // 반전 알고리즘
	// 메모리 할당
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printImage();
}

void bwImage() { // 흑백 알고리즘
	// 메모리 할당
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	// 입력 배열 --> 출력 배열
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