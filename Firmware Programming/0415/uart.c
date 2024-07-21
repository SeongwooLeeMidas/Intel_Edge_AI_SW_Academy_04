/*
 * uart.c
 *
 *  Created on: Apr 11, 2024
 *      Author: IOT
 */
#include <stdbool.h>
#include <stdio.h>
#include "uart.h"

extern UART_HandleTypeDef huart3;

static uint8_t rxdata[1];
//static bool rxd_flag = false;

#define D_BUF_OBJ_MAX	3

static BUF_T gBufObjs[D_BUF_OBJ_MAX];


// static void * FUN_NAME: 이거는 그냥 함수 이름을
static void(*uart_cbf)(void*);

void uart_init(void)
{
	for (int i=0; i<D_BUF_OBJ_MAX; i++) {
		gBufObjs[i].idx = 0;
		gBufObjs[i].flag = false;
	}

	// interrupt 방식으로 수신을 받는 함수
	// UART로 받은 정보를 어디에 저장할지 지정해주는 함수
	HAL_UART_Receive_IT(&huart3, (uint8_t *)&rxdata[0], 1);
	// 여기에 브레이크 걸고 디버깅 해보면 레지스터들이 설정됨
	// RXNEIE 설정: 들어와서 안 비어있다는게 바뀜
	// 컴포트 마스터에서 보내면 인터럽트가 걸려서
	// 레지스터 등에 값들 셋팅하는 걸 볼 수 있음
}

void uart_regcbf(void (*cbf)(void *))
{
	uart_cbf = cbf;
}

//// 정보를 받았다면 받은 정보를 출력해주는 함수
//void uart_thread(void *arg)
//{
//	for(int i=0; i<D_BUF_OBJ_MAX; i++){
//		if(gBufObjs[i].flag){
//			if(uart_cbf != NULL)	uart_cbf((void*)&gBufObjs[i]);
//
//			gBufObjs[i].idx = 0;
//			gBufObjs[i].flag = false;
//		}
//	}
//}


// interrupt 서비스 루틴 (ISR)
// UART로 정보가 들어오면 호출되는 함수
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	volatile uint8_t rxd;

	if (huart == &huart3) {
		rxd = rxdata[0];
		HAL_UART_Receive_IT(huart, (uint8_t *)&rxdata[0], 1);

		BUF_T *p = (BUF_T*)&gBufObjs[0];

		if(!p->flag){
			p->buf[p->idx] = rxd;
			//p->idx++;
			//p->idx %= D_BUF_MAX;
			if (p->idx < D_BUF_MAX) p->idx++;

			if (rxd == '\r' || rxd == '\n') {
				p->buf[p->idx] = 0;	// == '\0' == NULL
				p->flag = true;
				if(uart_cbf != NULL)	uart_cbf((void*)&gBufObjs[0]);
				p->idx = 0;
				p->flag = false;
			}
		}
	}
}
