/*
 * uart.c
 *
 *  Created on: Apr 11, 2024
 *      Author: IOT
 */
#include <stdbool.h>
#include <stdio.h>
#include "uart.h"
#include "slip.h"

// extern: 외부의 것을 써라
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;		// idx = 1

// uart 갯수에 맞춰서 늘리기 위한 변수
#define D_BUF_OBJ_MAX	3
static uint8_t rxdata[D_BUF_OBJ_MAX];
//static bool rxd_flag = false;
static BUF_T gBufObjs[D_BUF_OBJ_MAX];


// static void * FUN_NAME: 이거는 그냥 함수 이름을
static void(*uart_cbf[D_BUF_OBJ_MAX])(void*);
/* 위에거랑 같은거
 * static UART_CBF uart_cbf[D_BUF_OBJ_MAX];
 * */

void uart_init(void)
{
	for (int i=0; i<D_BUF_OBJ_MAX; i++) {
		gBufObjs[i].idx = 0;
		gBufObjs[i].flag = false;
	}

	// interrupt 방식으로 수신을 받는 함수
	// UART로 받은 정보를 어디에 저장할지 지정해주는 함수
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&rxdata[E_UART_0], 1);	// uart2
	HAL_UART_Receive_IT(&huart3, (uint8_t *)&rxdata[E_UART_1], 1);	// uart3
	// 여기에 브레이크 걸고 디버깅 해보면 레지스터들이 설정됨
	// RXNEIE 설정: 들어와서 안 비어있다는게 바뀜
	// 컴포트 마스터에서 보내면 인터럽트가 걸려서
	// 레지스터 등에 값들 셋팅하는 걸 볼 수 있음
}

bool uart_regcbf(uint8_t idx, UART_CBF cbf)
{
	if (idx > D_BUF_OBJ_MAX) return false;
	uart_cbf[idx] = cbf;
	return true;
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
// UART로 정보가 들어오면 호출되는 함수 (전부 받고 나서 호풀됨)
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	volatile uint8_t rxd;
	static uint8_t state = 0;

	if(huart == &huart2){		// idx = 0
		rxd = rxdata[E_UART_0];
		HAL_UART_Receive_IT(huart, (uint8_t *)&rxdata[E_UART_0], 1);

		BUF_T *p = (BUF_T*)&gBufObjs[E_UART_0];
		p->buf[p->idx] = rxd;

		slip_decode(&state, rxd, p, (UART_CBF)uart_cbf[0]);
	}

	if (huart == &huart3) {		// idx = 1
		rxd = rxdata[E_UART_1];
		HAL_UART_Receive_IT(huart, (uint8_t *)&rxdata[E_UART_1], 1);

		BUF_T *p = (BUF_T*)&gBufObjs[E_UART_1];

		if(!p->flag){
			p->buf[p->idx] = rxd;

			// state machine이라고 말한 분석 부분
			slip_decode(&state, rxd, p, (UART_CBF)uart_cbf[1]);


#if 0

			//p->idx++;
			//p->idx %= D_BUF_MAX;
			if (p->idx < D_BUF_MAX) p->idx++;

			if (rxd == '\r' || rxd == '\n') {
				p->buf[p->idx] = 0;	// == '\0' == NULL
				p->flag = true;
				if (uart_cbf[1] != NULL) uart_cbf[1]((void *)&gBufObjs[E_UART_1]);
				p->idx = 0;
				p->flag = false;
			}
#endif

		}
	}
}
