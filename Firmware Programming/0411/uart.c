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

static uint8_t rxd;
static bool rxd_flag = false;

//#define D_BUF_MAX	100
//typedef struct {
//  uint8_t buf[D_BUF_MAX+1];
//  uint8_t idx;
//  uint8_t flag;
//} BUF_T;
//
//static BUF_T gBufObjs[3];


void uart_init(void)
{
	// UART로 받은 정보를 어디에 저장할지 지정해주는 함수
	HAL_UART_Receive_IT(&huart3, (uint8_t *)&rxd, 1);
	// 여기에 브레이크 걸고 디버깅 해보면 레지스터들이 설정됨
	// RXNEIE 설정: 들어와서 안 비어있다는게 바뀜
	// 컴포트 마스터에서 보내면 인터럽트가 걸려서
	// 레지스터 등에 값들 셋팅하는 걸 볼 수 있음
}

// 정보를 받았다면 받은 정보를 출력해주는 함수
void uart_thread(void *arg)
{
	if (rxd_flag == true) {
		rxd_flag = false;
		printf("rxd:%c\r\n", rxd);
	}
}

// UART로 정보가 들어오면 호출되는 함수
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	// 정보를 받았다고 플래그를 설정
	rxd_flag = true;
	HAL_UART_Receive_IT(&huart3, (uint8_t *)&rxd, 1);
}
