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
// unsigned char inImage[height][width], outImage[height][width];
unsigned char** inImage, ** outImage;


/////////////////////
// 함수 선언부
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
// 함수 정의부
/////////////////////
/// 공통 함수
//////////////
void printMenu() {
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("0.열기  1.저장  9. 종료");
	puts("A.동일 B.밝게 C.어둡게 D.반전 E.흑백 F.축소 G.확대(포워딩) H.확대(백워딩) ~~~~");
	puts("I.회전 K.회전(중앙,백워딩)");
	puts("L.좌우대칭 M.상하대칭");
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
	char fullName[200] = "C:/RAW/";   // 저장된 경로 지정
	
	char tmpName[50];
	printf("파일명-->"); // 예를 들어 flower512, LENA256 같은 파일명
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");  // 확장자 추가해서 완전한 경로
	strcpy(fileName, fullName); // fileName에 복사

	// (중요!) 이미지의 폭과 높이를 결정
	rfp = fopen(fileName, "rb");  // 바이너리 모드로 열고
	fseek(rfp, 0L, SEEK_END); // 파일의 끝으로 이동
	long long fsize = ftell(rfp); // 나 어디쯤이지?  262,144  --> 512, 파일 크기 구함
	fclose(rfp);

	// 메모리 해제
	freeInputMemory();

	// 입력 영상 높이, 폭 구하기
	inH = inW = (int)sqrt(fsize);  // 제곱근을 구하는 이유: 정사각형일 때 폭=넓이여서

	// 메모리 할당
	mallocInputMemory();  // 입력 이미지에 필요한 메모리 할당

	inImage = (unsigned char**)malloc(sizeof(unsigned char*) * inH); // 이미지 픽셀 저장하기 위해 메모리 할당
	for (int i = 0; i < inH; i++)
		inImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * inW);

	// 파일 --> 메모리
	rfp = fopen(fileName, "rb");
	for (int i = 0; i < inH; i++)
		fread(inImage[i], sizeof(unsigned char), inW, rfp);  // 이미지 파일 내용을 메모리에 로드, 입력 이미지 픽셀 값 메모리에 저장
	fclose(rfp);

	// printf("%d ", inImage[100][100]);

	equalImage(); // 이미지 처리. 입력 = 출력 이미지 생성, 입력 이미지 출력에 복사 등
}

void saveImage() {
	if (outImage == NULL) // 출력 이미지 없을 때 함수 종료. 오류 방지로 씀
		return;

	char fullName[200] = "C:/RAW/";
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
		free(inImage[i]); // 오른쪽에 있는 2차원 배열 해제
	free(inImage); // 그거보다 왼쪽에 있는 1차원 배열 해제
	inImage = NULL;
}

void freeOutputMemory() {
	if (outImage == NULL)
		return;
	for (int i = 0; i < outH; i++)
		free(outImage[i]); // 오른쪽에 있는 2차원 배열 해제
	free(outImage); // 그거보다 왼쪽에 있는 1차원 배열 해제
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
//  영상처리 함수
////////////////////
void equalImage() { // 동일영상 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!!!) 출력 이미지의 크기를 결정 -> 알고리즘에 의존
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
	// (중요!!!) 출력 이미지의 크기를 결정 -> 알고리즘에 의존
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
	// (중요!!!) 출력 이미지의 크기를 결정 -> 알고리즘에 의존
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
	// (중요!!!) 출력 이미지의 크기를 결정 -> 알고리즘에 의존
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
	// (중요!!!) 출력 이미지의 크기를 결정 -> 알고리즘에 의존
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

void zoomOut() { // 축소 알고리즘
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();
	// (중요!!!) 출력 이미지의 크기를 결정 -> 알고리즘에 의존
	outH = (int)(inH / scale);
	outW = (int)(inW / scale); // 정수 정수여서 int 안 써도 되는데 int를 써서 정수로 명시해주는게 좋은 코드 작성 방식
	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i/scale)][(int)(k/scale)] = inImage[i][k];
		}
	}
	printImage();
}

void zoomIn() { // 확대 알고리즘 (포워딩)
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();
	// (중요!!!) 출력 이미지의 크기를 결정 -> 알고리즘에 의존
	outH = (int)(inH * scale);
	outW = (int)(inW * scale); // 정수 정수여서 int 안 써도 되는데 int를 써서 정수로 명시해주는게 좋은 코드 작성 방식
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

void zoomIn2() { // 확대 알고리즘 (백워딩)
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();
	// (중요!!!) 출력 이미지의 크기를 결정 -> 알고리즘에 의존
	outH = (int)(inH * scale);
	outW = (int)(inW * scale); // 정수 정수여서 int 안 써도 되는데 int를 써서 정수로 명시해주는게 좋은 코드 작성 방식
	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = inImage[(int)(i / scale)][(int)(k / scale)] ;
		}  // 나눠주는 이유는 입력 이미지를 scale만큼 확대하면 픽셀이 특정위치로 가잖아. 그래서 scale만큼 떨어지면
		   // 이상해지니까 i / scale 해주는거임 ㅇㅋ?
	}
	printImage();
}

void rotate() { // 회전 알고리즘 , 방향 마음에 안들면 - 붙여봐
	// 메모리 해제
	freeOutputMemory();
	// (중요!!!) 출력 이미지의 크기를 결정 -> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;

	// xd = cos*xs - sin*ys
	// yd = sin*xs + cos*ys , 컴퓨터 값에선 degree 말고 radian으로 처리함


	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int xs = i;
			int ys = k; // 이런 방식도 나쁘지 않을수도?
			int xd = (int)(cos(radian) * xs - sin(radian) * ys);
			int yd = (int)(sin(radian) * xs + cos(radian) * ys);

			// 회전시킨 위치가 밖이면 버려야돼
			if ((0<=xd && xd<outH) && (0<=yd && yd<outW))
			outImage[xd][yd] = inImage[xs][ys];
		}
	}
	printImage();
}

void rotate2() { // 회전 알고리즘 , 방향 마음에 안들면 - 붙여봐
	// 메모리 해제
	freeOutputMemory();
	// (중요!!!) 출력 이미지의 크기를 결정 -> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;

	// xd = cos*xs - sin*ys
	// yd = sin*xs + cos*ys , 컴퓨터 값에선 degree 말고 radian으로 처리함

	int cx = inH / 2; //center를 구해야댐
	int cy = inW / 2;

	for (int i = 0; i < outH; i++) { //백워딩이라 in말고 out
		for (int k = 0; k < outW; k++) {
			int xd = i;
			int yd = k; // 이런 방식도 나쁘지 않을수도?
			int xs = (int)(cos(radian) * (xd-cx) + sin(radian) * (yd-cy));
			int ys = (int)(-sin(radian) * (xd-cx) + cos(radian) * (yd-cy));
			xs += cx;
			ys += cy;

			// 회전시킨 위치가 밖이면 버려야돼
			if ((0 <= xs && xs < outH) && (0 <= ys && ys < outW))
				outImage[xd][yd] = inImage[xs][ys];
		}
	}
	printImage();
}

void shift() { // 이동 알고리즘
	int val = getIntValue();
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
			int new_i = i + val;
			int new_k = k + val;
			if (new_i >= 0 && new_i < outH && new_k >= 0 && new_k < outW)
				outImage[new_i][new_k] = inImage[i][k];
		}
	}
	printImage();
}

void mirrorLR() { //좌우대칭
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
			outImage[i][outW - k - 1] = inImage[i][k];
		}
	}
	printImage();
}
void mirrorXY() { //상하대칭
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
			outImage[outH - i - 1][k] = inImage[i][k];
		}
	}
	printImage();
}