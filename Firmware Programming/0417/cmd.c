/*
 * cmd.c
 *
 *  Created on: Apr 17, 2024
 *      Author: IOT
 */

// Comand line interface
// 텍스트 기반의 동작 인터페이스

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "cmsis_os.h"
#include "uart.h"
#include "app.h"
#include "main.h"
#include "button.h"
#include "type.h"
#include "led.h"
#include "cli.h"
#include "mem.h"
#include "cmd.h"


static osThreadId_t cmd_thread_hnd;			// 쓰레드 핸들
static osMessageQueueId_t cmd_msg_id;  		// 메시지 큐

static const osThreadAttr_t cmd_thread_attr = {
  .stack_size = 128 * 8,
  .priority = (osPriority_t) osPriorityNormal,
};


static void cmd_msg_put(void *arg);


void cmd_thread(void* arg){

	//uint32_t flags;
	(void)arg;
	osStatus sts;
	MSG_T rxMsg;

	uart_regcbf(E_UART_1, cmd_msg_put);

	while (1) {
		sts = osMessageQueueGet(cmd_msg_id, &rxMsg, NULL, osWaitForever);

		if(sts == osOK){
			// 메세지의 구분을 위한 switch
			switch(rxMsg.id){
				case E_MSG_CMD: {
				MEM_T *pMem = (MEM_T *)rxMsg.body.vPtr;
				PKT_T *pRxPkt = (PKT_T *)pMem->buf;

					switch (pRxPkt->cmd) {
						case E_CMD_LED : {
							printf("LED command\r\n");
							mem_free(pMem);
						} break;

						case E_CMD_CLI: {
							printf("CLI command\r\n");
							pRxPkt->ctx[pRxPkt->length] = 0; //'\0';
							cli_msg_put((void *)pMem);
						} break;
					}
				} break;
			}
		}
	}
}

void cmd_init(void)
{
	//cmd_evt_id = osEventFlagsNew(NULL);
	cmd_msg_id = osMessageQueueNew(3, sizeof(MSG_T), NULL);

	if (cmd_msg_id != NULL) printf("CMD Message Queue Created...\r\n");
	else {
		printf("CMD Message Queue Create Fail...\r\n");
		while (1);
	}

	cmd_thread_hnd = osThreadNew(cmd_thread, NULL, &cmd_thread_attr);
	if (cmd_thread_hnd != NULL) printf("CMD Thread Created...\r\n");
	else {
		printf("CMD Thread Create Fail...\r\n");
		while (1);
	}
}


// ISR
static void cmd_msg_put(void *arg){

	BUF_T *pBuf = (BUF_T*)arg;

	// ISR이라 대기 시간 0
	MEM_T *pMem = mem_alloc(100, 0);

	if(pMem !=NULL){
		memcpy(pMem->buf, pBuf, pBuf->idx);
		Q_PUT(cmd_msg_id, E_MSG_CMD, pMem, 0);
	}
}

