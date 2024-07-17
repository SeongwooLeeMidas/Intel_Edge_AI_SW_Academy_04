#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> // GUI 지원 가능!


/////////////////////
// 전역 변수부
/////////////////////
HWND hwnd; // 윈도우 화면(외부, 물리적), 안 중요함(실무에 안씀)
HDC hdc; // 윈도우 화면(내부, 논리적)

FILE* rfp;
char fileName[200];
#define height 512
#define width 512
// 메모리 확보
unsigned char inImage[height][width], outImage[height][width];

/////////////////////
// 함수 선언부
/////////////////////
void loadImage(); int getIntValue(); void printImage(); void printMenu();
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
			printf("%3d ", outImage[i][k]);
		}
		printf("\n");
	}
	printf("\n");
}
void loadImage() {
	char fullName[200] = "D:/RAW/Pet_RAW(squre)/Pet_RAW(512x512)/";
	char tmpName[50];
	printf("파일명-->"); // cat01, dog05
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, "_512.raw");
	strcpy(fileName, fullName);

	rfp = fopen(fileName, "rb");
	fread(inImage, sizeof(unsigned char), height * width, rfp);
	fclose(rfp);
	equalImage();
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
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	printImage();
}
void addImage() { // 더하기 알고리즘
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
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printImage();
}

void bwImage() { // 흑백 알고리즘
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