/*
 * pooling_thread.c
 *
 *  Created on: Apr 11, 2024
 *      Author: iot00
 */


// polling이라는 현재 층이 존재하는 이유는
// 갖가지 thread의 실행 타이밍을 모아서 한번에 조작하기 위함

// 따라서 원래라면 버튼 또한 이곳으로 편입되어야했으나
// 아까 설명하시기를 더 헷갈릴까봐 아직 이쪽에 포함하지 않으셨다고함.


#include <stdio.h>
#include <stdbool.h>
#include "adc.h"
#include "polling.h"

static void adc_callback(void *arg);


typedef struct {
	uint32_t period, count;
	bool flag;
	void (*cbf)(void *);
} THR_T; // thread type

volatile THR_T gThrObjs[]  = {
	// adc의 실행 주기를 500ms, 콜백함수를 설정
	{ .period = 500, 	.cbf = adc_thread		},
	{ .cbf = NULL			}
};


void polling_init(void)
{
	adc_init();
	// adc의 콜백함수를 해당 층에서 재정의
	adc_regcbf(0, adc_callback);
}


// 해당 레이어에 포함되어 있는 요소들의 flag를 확인하여 처리할 시기가 된 함수를 호출
void polling_thread(void *arg)
{
	static uint16_t thr_idx = 0;

	// 여러 작업을 한번에 모아 처리하는 특성상
	// app단에 바로 올라가 있는 uart나 button에 비해 우선 순위가 낮은 것으로 보임
	//		(왜? 배열에 들어가 있는 것 중 호출 1회당 thr_idx거 하나만 보고 나가기 때문에)
	if (gThrObjs[thr_idx].flag == true) {
		gThrObjs[thr_idx].flag = false;
		gThrObjs[thr_idx].cbf(NULL);
	}
	thr_idx++;
	if (gThrObjs[thr_idx].cbf == NULL) thr_idx = 0;
}

// adc의 콜백함수 재정의
static void adc_callback(void *arg)
{
	printf("adc value = %d\r\n", *(uint16_t *)arg);
}


// io.c 파일 HAL_IncTick() 함수에서 호출
// HAL_IncTick() 함수는 systick irq handler에서 호출됨(인터럽트 서비스 루틴임)
// 1ms 마다 호출됨
// 폴링에 포함되어있는 thread들의 count를 올리고 주기가 되었다면 플래그를 참값으로 함
void polling_update(void)
{
	for (int i=0; gThrObjs[i].cbf != NULL; i++) {
		gThrObjs[i].count++;
		gThrObjs[i].count %= gThrObjs[i].period;
		if (gThrObjs[i].count == 0) gThrObjs[i].flag = true;
	}
}
