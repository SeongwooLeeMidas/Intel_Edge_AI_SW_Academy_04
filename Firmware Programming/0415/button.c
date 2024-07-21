/*
 * button.c
 *
 *  Created on: Apr 11, 2024
 *      Author: iot00
 */
#include <stdbool.h>
#include <stdio.h>
#include "gpio.h"
#include "button.h"

#define D_BTN_BLUE_NO	13
#define D_BUTTON_MAX	1

static BUTTON_T gBtnObjs[D_BUTTON_MAX];

static void io_exti_btn_blue_callback(uint8_t rf, void *arg);


void button_init(void)
{
	gBtnObjs[0].no = 0;
	gBtnObjs[0].prev_tick = HAL_GetTick();

	io_exti_regcbf(D_BTN_BLUE_NO, io_exti_btn_blue_callback);
}

// call back 재정의
bool button_regcbf(uint16_t idx, BUTTON_CBF cbf)
{
	if (idx > D_BUTTON_MAX) return false;
	gBtnObjs[idx].cbf = cbf;
	return true;
}

// blue button인지 확인해 출력
void button_proc_blue(void *arg)
{
	BUTTON_T *p = &gBtnObjs[0];
	if (p->no == D_BTN_BLUE_NO) {
		printf("rf:%d, no:%d\r\n", p->edge,  p->no);
	}
}

// 이전 입력부터 120 tick이 지났으면 처리하는 함수
// 더미 역할
static void io_exti_btn_blue_callback(uint8_t rf, void *arg)
{
	volatile uint32_t curr_tick = HAL_GetTick();

	BUTTON_T *p = &gBtnObjs[0];

	if (curr_tick - p->prev_tick > 120) {
		p->prev_tick = curr_tick;
		p->edge = rf;
		p->no = *(uint16_t *)arg;
		if (p->cbf != NULL) p->cbf((void *)p);
	}
}
