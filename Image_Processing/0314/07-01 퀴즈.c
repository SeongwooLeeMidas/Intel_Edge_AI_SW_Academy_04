#define _CRT_SECURE_NO_WARNINGS // scanf_s 안쓰려고
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <Windows.h> // GUI 지원 기능

//////////////////
// 전역 변수부
//////////////////
HWND hwnd; // 윈도우 화면(외부, 물리적)
HDC hdc; // 윈도우 화면(내부, 논리적)

FILE* rfp, * wfp;
char fileName[200];
int inH, inW, outH, outW;
// 메모리 확보
// unsigned char inImage[height][width], outImage[height][width];
unsigned char** inImage, ** outImage;

//////////////////
// 함수 선언부
//////////////////
void loadImage(); int getIntValue(); void printImage(); void printMenu(); void saveImage();
void freeInputMemory(); void freeOutputMemory();
void mallocInputMemory(); void mallocOutputMemory(); // 메모리 할당, 출력 이미지에 할당된 메모리 해제

void equalImage(); void addImage(); void darkImage(); void grayImage();
void gammaImage(); void reverseImage(); void parabolCapImage(); // 감마 보정, 파라볼 캡
void andImage(); void orImage(); void xorImage();


//////////////////
// 메인 함수부
//////////////////

void main() {
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(NULL); // Windows 10 : hwnd, Windows 11 : NULL

	char inKey = 0;
	while (inKey != '9') { // 메뉴 호출
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
// 함수 정의부
//////////////////
// 공통 함수
/////////////

void printMenu() { // 메뉴 만들기
	puts("## GrayScale Image Processing (Beta 4) ##");
	puts("0.열기 1.저장  9.종료");
	puts("A.동일 B.밝게 C.어둡게 D.반전 E.흑백 F.감마 G.파라볼라 CAP H.파라볼라 CUP I.AND 처리 J.OR 처리 H.XOR 처리");
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
	printf("파일명--> "); // flower512, LENA256
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	// (중요!) 이미지의 폭과 높이를 결정
	rfp = fopen(fileName, "rb");
	fseek(rfp, 0L, SEEK_END); // 파일의 끝으로 이동
	long long fsize = ftell(rfp); // 나 어디쯤이지? 262,144 --> 512
	fclose(rfp);

	// 메모리 해제
	freeInputMemory();

	// 높이, 폭 구하기
	inH = inW = (int)sqrt(fsize);

	// 메모리 할당
	mallocInputMemory();

	inImage = (unsigned char**)malloc(sizeof(unsigned char*) * inH);
	for (int i = 0; i < inH; i++)
		inImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * inW);

	// 파일 --> 메모리

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
	printf("파일명--> "); // out01, out02...
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, "_512.raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");
	// 메모리 --> 파일 (한 행씩)
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	fclose(wfp);
	//MessageBox(hwnd, L"저장 완료", L"저장 창", NULL);
}

int getIntValue() {  // 정수 값을 입력받으니 int형으로, void 쓰면 값을 반환 못함
	int retValue;
	printf("정수 값--> ");
	scanf("%d", &retValue);
	return retValue;
}



/////////////////
// 영상 처리 함수
/////////////////

void equalImage() { // 동일영상 알고리즘

	// 메모리 할당
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * inH);
	for (int i = 0; i < inH; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * inW);

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	printf("원본 이미지 파일\n");
	printImage();
}

void addImage() { // 더하기(밝게) 알고리즘

	// 메모리 할당
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
	printf("밝게 처리\n");
	printImage();
}

void darkImage() { // 어둡게 알고리즘

	// 메모리 할당
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
	printf("어둡게 처리\n");
		printImage();
}

void grayImage() { // 흑백 처리 알고리즘

	// 메모리 할당
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
	printf("흑백 처리\n");
	printImage();
}

void reverseImage() { // 반전 알고리즘

	//
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printf("반전 처리\n");
	printImage();
}

void gammaImage() { // 감마 처리 알고리즘

	// 메모리 할당
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char**)malloc(sizeof(unsigned char*) * width);

	float gamma;
	printf("감마 처리 (0~10) --> ");
	scanf("%f", &gamma); // 감마 값을 입력 받음

	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			//픽셀 값 0~1로 정규화
			float normalized_pixel = (float)inImage[i][k] / 255.0;
			//감마 함수 적용후 보정된 값 계산
			float corrected_pixel = pow(normalized_pixel, gamma);

			corrected_pixel *= 255.0;

			if (corrected_pixel < 0)
				corrected_pixel = 0;
			if (corrected_pixel > 255)
				corrected_pixel = 255;

			outImage[i][k] = (unsigned char)corrected_pixel;
		}
	}
	printf("감마 처리\n");
	printImage();
}

void parabolCapImage() { // 파라볼라 Cap 처리 알고리즘

	//메모리 할당
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
	printf("파라볼라 CAP 처리\n");
	printImage();
}

void parabolCupImage() { // 파라볼라 Cup 처리 알고리즘

	//메모리 할당
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
	printf("파라볼라 CUP 처리\n");
	printImage();
}

void andImage() { // And 처리 알고리즘

	//메모리 할당
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = inImage[i][k] & inImage[i][k];
		}
	}
	printf("And 처리 알고리즘");
	printImage();
}

void orImage() { // Or 처리 알고리즘

	// 메모리 할당
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = inImage[i][k] | inImage[i][k];

			// 결과 값이 255를 초과하면 255로 설정
			if (outImage[i][k] > 255)
				outImage[i][k] = 255;
		}
	}
	printf("Or 처리 알고리즘");
	printImage();
}

void xorImage() { // XOR 처리 알고리즘

	// 메모리 할당
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (int i = 0; i < height; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);

	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			outImage[i][k] = inImage[i][k] ^ inImage[i][k];

			// 결과 값이 255를 초과하면 255로 설정
			if (outImage[i][k] > 255)
				outImage[i][k] = 255;
		}
	}
	printf("XOR 처리 알고리즘");
	printImage();
}