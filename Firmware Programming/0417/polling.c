/*
 * pooling_thread.c
 *
 *  Created on: Apr 11, 2024
 *      Author: iot00
 */


// polling이라는 현재 층이 존재하는 이유는
// 갖가지 thread의 실행 타이밍을 모아서 한번에 조작하기 위함


#include <stdio.h>
#include "cmsis_os.h"
#include "button.h"
#include "polling.h"
#include "type.h"

static osThreadId_t polling_thread_hnd;			// 쓰레드 핸들
static osMessageQueueId_t polling_msg_id;  		// 메시지 큐


static const osThreadAttr_t polling_thread_attr = {
  .stack_size = 128 * 8,
  .priority = (osPriority_t) osPriorityNormal,
};


void polling_thread_init(void);
static void btn_blue_callback(void *arg);
static void btn_uart_callback(void *arg);


static void polling_thread(void *arg)
{

	//uint32_t flags;
	(void)arg;
	osStatus sts;
	MSG_T rxMsg;

	printf("Polling Thread Started...\r\n");

	button_init();
	button_regcbf(E_BTN_BLUE, btn_blue_callback);
	button_regcbf(E_BTN_UART, btn_uart_callback);

	// button에서 들어온 플래그에 따라서 처리
	while (1) {

		sts = osMessageQueueGet(polling_msg_id, &rxMsg, NULL, osWaitForever);

		if(sts == osOK){
			// 메세지의 구분을 위한 switch
			switch(rxMsg.id){
				case E_BTN_BLUE : {
					printf("%s[0x0001][%d]\r\n", __func__, __LINE__);
					button_proc_blue(NULL);
				} break;

				case E_BTN_UART: {
					printf("%s[0x0008][%d]\r\n", __func__, __LINE__);
					button_proc_uart(NULL);
				} break;
			}
		}
	}
}

void polling_init(void)
{
	//polling_evt_id = osEventFlagsNew(NULL);
	polling_msg_id = osMessageQueueNew(3, sizeof(MSG_T), NULL);

	if (polling_msg_id != NULL) printf("Polling Message Queue Created...\r\n");
	else {
		printf("Polling Message Queue Create Fail...\r\n");
		while (1);
	}

	polling_thread_hnd = osThreadNew(polling_thread, NULL, &polling_thread_attr);
	if (polling_thread_hnd != NULL) printf("Pooling Thread Created...\r\n");
	else {
		printf("Pooling Thread Create Fail...\r\n");
		while (1);
	}
}

static void btn_blue_callback(void *arg)
{
	//uint32_t flags;
	(void)arg;
	MSG_T txMsg;

	txMsg.id = E_BTN_BLUE;
	osMessageQueuePut(polling_msg_id, &txMsg, 0, 0);
}

static void btn_uart_callback(void *arg)
{
	//uint32_t flags;
	(void)arg;
	MSG_T txMsg;

	txMsg.id = E_BTN_UART;
	osMessageQueuePut(polling_msg_id, &txMsg, 0, 0);
}
