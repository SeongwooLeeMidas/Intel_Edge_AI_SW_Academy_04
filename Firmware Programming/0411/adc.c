/*
 * adc.c
 *
 *  Created on: Apr 9, 2024
 *      Author: iot00
 */

#include <stdio.h>
#include "adc.h"

// 오류가 안나게 하기 위한 더미 함수
static void adc_dummy(void *);

// 숫자를 저장하는 구조체 배열 선언
static ADC_T gAdcObjs[] = {
	{ .cbf = adc_dummy 	},
	{ .cbf = NULL			}
};

// adc 초기화 함수
void adc_init(void)
{
}

// adc의 call back function을 reset하기 위한 함수
void adc_regcbf(uint16_t idx, ADC_CBF cbf)
{
	gAdcObjs[idx].cbf = cbf;
}

// adc에 있는 값을 갱신해주는 함수
void adc_thread(void *arg)
{
	(void)arg;

	static uint16_t value = 100;

	for (int i=0; gAdcObjs[i].cbf != NULL; i++) {
		value+=100;
		gAdcObjs[i].value = value;
		gAdcObjs[i].cbf((void *)&gAdcObjs[i].value);
	}
}

//--------------
// adc_hw()

static void adc_dummy(void *)
{
	printf("I'm ADC dummy\r\n");
	return;
}
