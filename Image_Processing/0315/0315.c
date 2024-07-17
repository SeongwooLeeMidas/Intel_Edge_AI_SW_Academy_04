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
int height;
int width;
// 메모리 확보
// unsigned char inImage[height][width], outImage[height][width];
unsigned char** inImage = NULL, ** outImage = NULL;

//////////////////
// 함수 선언부
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
// 메인 함수부
//////////////////

void main() {
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(NULL); // Windows 10 : hwnd, Windows 11 : NULL

	char inKey = 0;
	while (inKey != '9') { // 메뉴 호출
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
// 함수 정의부
//////////////////
// 공통 함수
/////////////

void printMenu() { // 메뉴 만들기
	puts("## GrayScale Image Processing (Beta 4) ##");
	puts("0.열기 1.저장  9.종료");
	puts("A.동일 / B.밝게 / C.어둡게 / D.반전 / E.흑백 / F.감마 / G.파라볼라 CAP");
	puts("H.파라볼라 CUP / I.AND 처리 / J.OR 처리 / H.XOR 처리 / L.축소");
	puts("M.확대(포워딩) / N.확대(백워딩) / Q.회전 / R.회전(중앙, 백워딩)");
	puts("S.이동 / P.히스토그램 스트레칭 / O. 엔드-인 / V. 평활화 / U. 반전");
	puts("X. 엠보싱 / Z. 블러 / W. 샤프닝");
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
	//메모리 해제
	freeInputMemory();
	// 입력 영상 높이, 폭 구하기
	inH = inW = (int)sqrt(fsize);
	// 메모리 할당
	mallocInputMemory();

	// 파일 --> 메모리
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
	printf("파일명--> "); // out01, out02...
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");
	// 메모리 --> 파일 (한 행씩)
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	fclose(wfp);
	MessageBox(hwnd, L"저장 완료", L"저장 창", NULL);
}

int getIntValue() {
	int retValue;
	printf("정수 값--> ");
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
// 영상 처리 함수
/////////////////

void equalImage() { // 동일영상 알고리즘

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

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

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
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
	printf("밝게 처리\n");
	printImage();
}

void darkImage() { // 어둡게 알고리즘

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
	int val = getIntValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] - val > 0)
				outImage[i][k] = inImage[i][k] - val;
			else
				outImage[i][k] = 0;
		}
	}
	printf("어둡게 처리\n");
	printImage();
}

void grayImage() { // 흑백 처리 알고리즘

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
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

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printf("반전 처리\n");
	printImage();
}

void gammaImage() { // 감마 처리 알고리즘

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	float gamma;
	printf("감마 처리 (0~10) --> ");
	scanf("%f", &gamma); // 감마 값을 입력 받음

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
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

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++)
	{
		for (int k = 0; k < inW; k++)
		{
			outImage[i][k] = 255 - 255 * pow((inImage[i][k] / 128 - 1), 2);
		}
	}
	printf("파라볼라 CAP 처리\n");
	printImage();
}

void parabolCupImage() { // 파라볼라 Cup 처리 알고리즘

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++)
	{
		for (int k = 0; k < inW; k++)
		{
			outImage[i][k] = 255 * pow((inImage[i][k] / 128 - 1), 2);
		}
	}
	printf("파라볼라 CUP 처리\n");
	printImage();
}

void andImage() { // And 처리 알고리즘

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][k] & inImage[i][k];
		}
	}
	printf("And 처리 알고리즘");
	printImage();
}

void orImage() { // Or 처리 알고리즘

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
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

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			outImage[i][k] = inImage[i][k] ^ inImage[i][k];

			// 결과 값이 255를 초과하면 255로 설정
			if (outImage[i][k] > 255)
				outImage[i][k] = 255;
		}
	}
	printf("XOR 처리 알고리즘");
	printImage();
}

void zoomOut() { // 축소 알고리즘
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = (int)(inH / scale);
	outW = (int)(inW / scale);

	// 메모리 할당
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i / scale)][(int)(k / scale)] = inImage[i][k];
		}
	}
	printf("축소");
	printImage();
}

void zoomIn() { // 포워딩 확대 알고리즘
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = (int)(inH * scale);
	outW = (int)(inW * scale);

	// 메모리 할당
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i * scale)][(int)(k * scale)] = inImage[i][k];
		}
	}
	printf("확대");
	printImage();
}

void zoomIn2() { // 백워딩 확대 알고리즘
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = (int)(inH * scale);
	outW = (int)(inW * scale);

	// 메모리 할당
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = inImage[(int)(i / scale)][(int)(k / scale)];
		}
	}
	printf("확대");
	printImage();
}
void rotate() { // 회전 알고리즘

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();
	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;
	// xd = cos(xs) - sin(ys)
	// yd = sin(xs) + cos(ys)

	// 입력 배열 --> 출력 배열
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
	printf("회전\n");
	printImage();
}

void rotate2() { // 회전(중앙, 백워딩) 알고리즘

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
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
	printf("회전 백워딩\n");
	printImage();
}

void histoStretch() { // 히스토그램 스트레칭 알고리즘

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	// 여기서부터 영상처리 알고리즘 시작~~
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
	printf("히스토그램 스트레칭\n");
	printImage();
}

void endIn() { // 엔드인 탐색 알고리즘

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	// 여기서부터 영상처리 알고리즘 시작~~
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
	printf("엔드-인\n");
	printImage();
}

void histoEqual() { // 히스토그램 평활화 알고리즘

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();


	// 1단계 : 빈도수 세기 (=히스토그램)
	int histo[256] = { 0. };
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			histo[inImage[i][k]]++;

	// 2단계 : 누적 히스토그램 생성
	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];
	for (int i = 1; i < 256; i++)
		sumHisto[i] = sumHisto[i - 1] + histo[i];


	// 3단계 : 정규화된 히스토그램 생성 normalHisto = sumHisto * (1.0 / (inH*inW) * 255.0;
	double normalHisto[256] = { 1.0, };
	for (int i = 0; i < 256; i++) {
		normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0;
	}
	// 4단계 : inImage를 정규화된 값으로 치환
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = (unsigned char)normalHisto[inImage[i][k]];
		}
	}
	printf("히스토그램 평활화\n");
	printImage();
}
void moveImage() { // 이미지 이동 알고리즘
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	int a = getIntValue();
	int b = getIntValue();
	int i, k = 0;
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			// 이미지 이동 시 경계를 벗어나는 경우를 고려하여 인덱스를 체크하여 처리
			if (i + a >= 0 && i + a < inH && k - b >= 0 && k - b < inW) {
				outImage[i][k] = inImage[i + a][k - b];
			}
			else {
				outImage[i][k] = 0; // 경계를 벗어나는 경우에는 0으로 처리하거나 다른 방법으로 처리
			}
		}
	}
	printf("이미지 이동\n");
	printImage();
}

void mirrorImage() {
	printf("1 = 상하 반전 or 2 = 좌우 반전\n");
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	int a = getIntValue();
	// 1일때는 좌우, 2일때는 상하 반전

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (a == 1)
				outImage[i][k] = inImage[inW - 1 - i][k];
			else
				outImage[i][k] = inImage[i][inH - 1 - k];
		}
	}
	printf("반전 \n");
	printImage();
}

void emboss() { // 화소영역 처리 : 엠보싱 알고리즘

	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {-1.0, 0.0, 0.0}, // 엠보싱 마스크
						  { 0.0, 0.0, 0.0},
						  { 0.0, 0.0, 1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++) // 2 대신 1씩만 더해도 되긴 함
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInImage[i + m][k + n] * mask[m][n];
				}
				tmpOutImage[i][k] = S;
			}
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void blur() { // 화소영역 처리 : 블러링 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {1. / 9, 1. / 9, 1. / 9}, // 블러링 마스크
						  {1. / 9, 1. / 9, 1. / 9},
						  {1. / 9, 1. / 9, 1. / 9} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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
void sharp() { // 화소영역 처리 : 샤프닝 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {0.0, -1.0 ,0.0}, // 샤프닝 마스크
						  {-1.0 ,5.0, -1.0},
						  {0.0, -1.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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