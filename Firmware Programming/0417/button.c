/*
 * button.c
 *
 *  Created on: Apr 11, 2024
 *      Author: iot00
 */
#include <stdbool.h>
#include <stdio.h>
#include "uart.h"
#include "gpio.h"
#include "button.h"

#define D_BTN_BLUE_NO	13
#define D_BUTTON_MAX	2

static BUTTON_T gBtnObjs[D_BUTTON_MAX];

// blue button callback
static void io_exti_btn_blue_callback(uint8_t rf, void *arg);
// uart call back
static void uart_btn_callback(void *arg);


void button_init(void)
{
	for(int i=0; i<D_BUTTON_MAX; i++){
		gBtnObjs[i].no = 0;
		gBtnObjs[i].prev_tick = HAL_GetTick();
	}
	io_exti_regcbf(D_BTN_BLUE_NO, io_exti_btn_blue_callback);
	uart_regcbf(E_UART_0, uart_btn_callback);
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
	BUTTON_T *p = &gBtnObjs[E_BTN_BLUE];
	if (p->no == D_BTN_BLUE_NO) {
		printf("rf:%d, no:%d\r\n", p->edge,  p->no);
	}
}

void button_proc_uart(void *arg)
{
	BUTTON_T *p = &gBtnObjs[E_BTN_UART];
	printf("%c:%d\r\n", p->no,  p->no);
}



// 이전 입력부터 120 tick이 지났으면 처리하는 함수
// 더미 역할
static void io_exti_btn_blue_callback(uint8_t rf, void *arg)
{
	volatile uint32_t curr_tick = HAL_GetTick();

	BUTTON_T *p = &gBtnObjs[E_BTN_BLUE];

	if (curr_tick - p->prev_tick > 120) {
		p->prev_tick = curr_tick;
		p->edge = rf;
		p->no = *(uint16_t *)arg;
		if (p->cbf != NULL) p->cbf((void *)p);
	}
}

//
static void uart_btn_callback(void *arg){

	BUF_T *pBuf = (BUF_T*)arg;

	BUTTON_T *p = &gBtnObjs[E_BTN_UART];
	p->no =(uint16_t)pBuf->buf[0];
	if (p->cbf != NULL) p->cbf((void *)p);

}
