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
int inH, inW, outH, outW;
// 메모리 확보
unsigned char** inImage = NULL, ** outImage = NULL;


/////////////////////
// 함수 선언부
/////////////////////
void loadImage(); int getIntValue(); void printImage(); void printMenu();
void saveImage(); void freeInputMemory(); void freeOutputMemory();
void mallocInputMemory(); void mallocOutputMemory();
double** mallocDoubleMemory(int, int); void freeDoubleMemory(double**, int);

// 화소점 처리
void equalImage(); void addImage(); void subImage(); void reverseImage();
void bwImage(); void gammaImage(); void parabolCapImage(); void parabolCupImage();
void andImage(); void orImage(); void xorImage();

// 기하학 처리
void zoomOut(); void zoomIn(); void zoomIn2(); void rotate(); void rotate2();
void histoStretch(); void endIn(); void histoEqual();

// 화소 영역 처리
void emboss(); void blur(); void sharp(); void edge1(); void edge2();
void Laplacian(); void GausianS(); void Median();
void MovingAverage(); void prewittVertical(); void sobelVertical();

void main() {
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(NULL);  // Windows 10 : hwnd

	char inKey = 0;
	while (inKey != '9') {
		printMenu();
		inKey = _getch();
		// system("cls");
		switch (inKey)
		{
		case '0': loadImage(); break;
		case '1': saveImage(); break;
		case '9': break;
		case 'a': case 'A': equalImage(); break;
		case 'b': case 'B': addImage(); break;
		case 'c': case 'C': subImage(); break;
		case 'd': case 'D': reverseImage(); break;
		case 'e': case 'E': bwImage(); break;
		case 'f': case 'F': gammaImage(); break;
		case 'g': case 'G': parabolCapImage(); break;
		case 'h': case 'H': parabolCupImage(); break;
		case 'i': case 'I': andImage(); break;
		case 'j': case 'J': orImage(); break;
		case 'k': case 'K': xorImage(); break;
		case 'l': case 'L': zoomOut(); break;
		case 'm': case 'M': zoomIn(); break;
		case 'n': case 'N': zoomIn2(); break;
		case 'o': case 'O': rotate(); break;
		case 'p': case 'P': rotate2(); break;
		case 'q': case 'Q': histoStretch(); break;
		case 'r': case 'R': endIn(); break;
		case 's': case 'S': histoEqual(); break;
		case 't': case 'T': emboss(); break;
		case 'u': case 'U': blur(); break;
		case 'v': case 'V': sharp(); break;
		case 'w': case 'W': edge1(); break;
		case 'x': case 'X': edge2(); break;
		case 'y': case 'Y': Laplacian(); break;
		case 'z': case 'Z': GausianS(); break;
		case '3': Median(); break;
		case '4': MovingAverage(); break;
		case '5': andImage(); break;
		case '6': prewittVertical(); break;
		case '7': sobelVertical(); break;
		}

	}
	freeInputMemory();
	freeOutputMemory();
}

/////////////////////
// 함수 정의부
/////////////////////
/// 공통 함수
//////////////
void printMenu() {
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("0.열기  1.저장  9.종료");
	puts("A.동일 B.밝게 C.어둡게 D.반전 E.흑백 F.감마 G.파라캡 H.파라컵 I.AND J.OR K.XOR");
	puts("L.축소 M.확대(포워딩) N.확대(백워딩) O.회전 P.회전(중앙,백워딩)");
	puts("Q.히스토그램 스트래칭 R.엔드-인 S.평활화");
	puts("T.엠보싱 U.블러링 V.샤프닝 W.수직 검출 X.수평 검출");
	puts("Y.라플라시안 Z.가우시안 스무딩 3.메디안");
	puts("4.이동 평균 5.프리윗 수직 6.소벨 수직");
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
	// 메모리 해제
	freeInputMemory();
	// 입력영상 높이, 폭 구하기
	inH = inW = (int)sqrt(fsize);
	// 메모리 할당
	mallocInputMemory();

	// 파일 --> 메모리
	rfp = fopen(fileName, "rb");
	for (int i = 0; i < inH; i++)
		fread(inImage[i], sizeof(unsigned char), inW, rfp);
	fclose(rfp);

	equalImage();
}

void saveImage() {
	if (outImage == NULL)
		return;
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("파일명-->"); // out01, out02......
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");
	// 메모리 --> 파일 (한행씩)
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	fclose(wfp);
	// MessageBox(hwnd, L"저장 완료", L"저장 창", NULL);
	printf("저장 완료");
}

int getIntValue() {
	int retValue;
	printf("정수값-->"); scanf("%d", &retValue);
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

//////////////////
//  영상처리 함수
////////////////////
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
	printImage();
}
void addImage() { // 더하기 알고리즘
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
			if (inImage[i][k] + val < 255)
				outImage[i][k] = inImage[i][k] + val;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();
}

void subImage() { // 빼기 알고리즘
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

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printImage();
}

void bwImage() { // 흑백 알고리즘
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
			if (inImage[i][k] > 127)
				outImage[i][k] = 255;
			else
				outImage[i][k] = 0;
		}
	}
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

void andImage() { // AND 처리 알고리즘

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	int val = getIntValue();

	// 입력 배열 --> 출력배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if ((inImage[i][k] & (unsigned char)val) >= 255)
				outImage[i][k] = 255;
			else if ((inImage[i][k] & (unsigned char)val) < 0)
				outImage[i][k] = 0;
			else
				outImage[i][k] = (unsigned char)(inImage[i][k] & (unsigned char)val);
		}
	}
	printImage();
}

void orImage() { // OR 처리 알고리즘

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	int val = getIntValue();
	// 입력 배열 --> 출력배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if ((inImage[i][k] | (unsigned char)val) >= 255)
				outImage[i][k] = 255;
			else if ((inImage[i][k] | (unsigned char)val) < 0)
				outImage[i][k] = 0;
			else
				outImage[i][k] = (unsigned char)(inImage[i][k] | (unsigned char)val);
		}
	}
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

	int val = getIntValue();
	// 입력 배열 --> 출력배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if ((inImage[i][k] ^ (unsigned char)val) >= 255)
				outImage[i][k] = 255;
			else if ((inImage[i][k] ^ (unsigned char)val) < 0)
				outImage[i][k] = 0;
			else
				outImage[i][k] = (unsigned char)(inImage[i][k] ^ (unsigned char)val);
		}
	}
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
	printImage();
}

void zoomIn() { // 확대 알고리즘
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
	printImage();
}

void zoomIn2() { // 확대 알고리즘
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
	// 입력 배열 --> 출력 배열
	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;
	// xd = cos*xs - sin*ys
	// yd = sin*xs + cos*ys

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int xs = i;
			int ys = k;
			int xd = (int)(cos(radian) * xs - sin(radian) * ys);
			int yd = (int)(sin(radian) * xs + cos(radian) * ys);

			if ((0 <= xd && xd < outH) && (0 <= yd && yd < outW))
				outImage[xd][yd] = inImage[xs][ys];
		}
	}
	printImage();
}

void rotate2() { // 회전 알고리즘 + 중앙/백워딩
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	int degree = getIntValue();
	double radian = -degree * 3.141592 / 180.0;
	// xd = cos*xs - sin*ys
	// yd = sin*xs + cos*ys

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
	printImage();
}

void  histoStretch() { // 히스토그램 스트래칭 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	// 진짜 영상처리 알고리즘
	// new = (old - low) / (high - low) * 255.0
	int high = inImage[0][0], low = inImage[0][0];
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k];
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

	// 진짜 영상처리 알고리즘
	// new = (old - low) / (high - low) * 255.0
	int high = inImage[0][0], low = inImage[0][0];
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k];
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
	// 1단계 : 빈도수 세기(=히스토그램) histo[256]
	int histo[256] = { 0, };
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			histo[inImage[i][k]]++;
	// 2단계 : 누적히스토그램 생성
	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];
	for (int i = 1; i < 256; i++)
		sumHisto[i] = sumHisto[i - 1] + histo[i];
	// 3단계 : 정규화된 히스토그램 생성  normalHisto = sumHisto * (1.0 / (inH*inW) ) * 255.0;
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
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2); // 테두리 확보를 위해 2 크게 할당
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];  // 인덱스 1 증가시키는 이유 역시 테두리 확보

	// *** 회선 연산 ***
	double S; // 각 픽셀에서 계산된 총 합을 저장하는 변수
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값. 각 픽셀에서의 합 초기화

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;  // 임시 출력 이미지에 저장
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 127.0; //어둡게

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

void sharp() { // 화소영역 처리 : 샤프닝
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
	double mask[3][3] = { { -1.0, -1.0, -1.0}, // 샤프닝 마스크
						  { -1.0,  9.0, -1.0},
						  { -1.0, -1.0, -1.0} };
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

void edge1() { // 화소영역 처리 : 수직검출 알고리즘
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
	double mask[3][3] = { {  0.0, 0.0, 0.0}, // 수직 에지 검출 마스크
						  { -1.0, 1.0, 0.0},
						  {  0.0, 0.0, 0.0} };
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

void edge2() { // 화소영역 처리 : 수평검출 알고리즘
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
	double mask[3][3] = { {  0.0, -1.0, 0.0}, // 수평 에지 검출 마스크
						  {  0.0,  1.0, 0.0 },
						  {  0.0,  0.0, 0.0 } };
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

void Laplacian() { // 화소영역 처리 : 라플라시안
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
	double mask[3][3] = { {  0.0, -1.0,  0.0}, // 라플라시안 마스크
						  { -1.0,  4.0, -1.0},
						  {  0.0, -1.0,  0.0} };
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

void GausianS() { // 화소영역 처리 : 가우시안 스무딩 알고리즘
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
	double mask[3][3] = { {1. / 16 ,1. / 8, 1. / 16},  // 가우시안 스무딩 마스크
							{1. / 8 , 1. / 4, 1. / 8 },
							{1. / 16 ,1. / 8, 1. / 16} };
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

void Median() { // 화소영역 처리 : 메디안 함수, 잡음 감소
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
	double mask[3][3] = { { 1.0, 1.0, 1.0 },  // 메디안 마스크
							{1.0, 1.0, 1.0 },
							{1.0, 1.0, 1.0 } };
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

void MovingAverage() { // 화소영역 처리 : 이동 평균 필터, 잡음 감소
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
	double mask[3][3] = { {1. / 9, 1. / 9, 1. / 9 },  // 이동 평균 마스크
							{1. / 9, 1. / 9, 1. / 9 },
							{1. / 9, 1. / 9, 1. / 9 } };
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

void prewittVertical() { // 화소영역 처리 : 프리윗 필터 수직, 경계 감지
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
	double mask[3][3] = { {  -1.0, 0.0, 1.0 },  // 프리윗 마스크
							{-1.0, 0.0, 1.0 },
							{-1.0, 0.0, 1.0 } };
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

void sobelVertical() { // 화소영역 처리 : 소벨 필터 수직, 엣지 강도 방향
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
	double mask[3][3] = { {  -1.0, 0.0, 1.0 },  // 소벨 수직 마스크
							{-2.0, 0.0, 2.0 },
							{-1.0, 0.0, 1.0 } };
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