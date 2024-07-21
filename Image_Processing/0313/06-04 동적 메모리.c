#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> 

void main()
{
	/*int size;
	size = 50;
	unsigned char ary[size];*/

	int size = 50;
	int* p; // 주소는 알아야지!!
	(int*) malloc(4*50); //50칸을 잡은 다음에 int형으로(4바이트) 잘라! 그래서 4x50임

	//*(p + 0) = 100; //p의 실제값 100
	//*(p + 1) = 101;
	//*(p + 2) = 102;
	p[0] = 100;
	p[1] = 200;
	p[2] = 300;

	printf("%d %d \n", *(p + 1), p[1]);

	free(p);

	// 퀴즈 : 정수형 동적 메모리 100칸 확보 후, 거기에 1234, 1235 ... 값을 대입하기
	// 그리고 합계 출력
	
	int SIZE = 100;
	int* p;
	p = (int*) malloc(sizeof(int) * SIZE);
	int num = 1234;
	for (int i = 0; i < SIZE; i++) {
		// *(p + i) = num;
		p[i] = num;
		num++;
	}
	long long hap=0;
	for (int i = 0; i < SIZE; i++)
		hap += p[i];
	printf("%ld ", hap);
	free(p);

	// 퀴즈 : 실수형 동적 메모리 5칸짜리를 2개 준비하고, 첫 번째에는 0.1 ~ 0.5까지 대입,
	// 두 번째에는 첫 번째를 역순으로 대입.

// 퀴즈: 실수형 동적 메모리 5칸짜리를 2개 준비하고, 첫번째에는 0.1 ~0.5까지 대입,
//			두번째에는 첫번째를 역순으로 대입.
	double* p;
	double* q;

	p = (double*)malloc(sizeof(double) * 5);
	q = (double*)malloc(sizeof(double) * 5);

	double value = 0.1;
	for (int i = 0; i < 5; i++) {
		p[i] = value;
		value += 0.1;
	}
	for (int i = 0; i < 5; i++)
		q[5 - 1 - i] = p[i];		// 두 배열의 크기는 같고 원소들을 반대 순서로 복사할 수 있음

	printf("%lf, %lf, %lf", q[0], q[1], q[2]);

	free(p);
	free(q);


}