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

static osThreadId_t polling_thread_hnd;			// 쓰레드 핸들
static osEventFlagsId_t polling_evt_id;			// 이벤트 플래그 핸들

static const osThreadAttr_t polling_thread_attr = {
  .stack_size = 128 * 8,
  .priority = (osPriority_t) osPriorityNormal,
};


void polling_thread_init(void);
static void btn_blue_callback(void *arg);

#define D_BTN_BLUE 	0
//static BUTTON_T gBtnBlue;

static void polling_thread(void *arg)
{
	uint32_t flags;
	(void)arg;

	printf("Polling Thread Started...\r\n");

	button_init();
	button_regcbf(D_BTN_BLUE, btn_blue_callback);

	// button에서 들어온 플래그에 따라서 처리
	while (1) {
		flags = osEventFlagsWait(polling_evt_id, 0xffff, osFlagsWaitAny, osWaitForever);

		if (flags & 0x0001) {
			printf("\r\n%s[0x0001][%d]\r\n", __func__, __LINE__);
			osEventFlagsSet(polling_evt_id, 0x0002);
			button_proc_blue(NULL);
		}

		if (flags & 0x0002) {
			printf("%s[0x0002][%d]\r\n", __func__, __LINE__);
			osEventFlagsSet(polling_evt_id, 0x0004);
		}

		if (flags & 0x0004) {
			printf("%s[0x0004][%d]\r\n", __func__, __LINE__);
		}
	}
}

void polling_init(void)
{
	polling_evt_id = osEventFlagsNew(NULL);
	if (polling_evt_id != NULL) printf("Polling Event Flags Created...\r\n");
	else {
		printf("Polling Event Flags Create File...\r\n");
		while (1);
	}

	polling_thread_hnd = osThreadNew(polling_thread, NULL, &polling_thread_attr);
	if (polling_thread_hnd != NULL) printf("Polling Thread Created...\r\n");
	else {
		printf("Polling Thread Create Fail...\r\n");
		while (1);
	}
}

static void btn_blue_callback(void *arg)
{
//	BUTTON_T *p;

//	if (arg == NULL) return;
//	p = (BUTTON_T *)arg;
//	gBtnBlue.edge = p->edge;
//	gBtnBlue.no = p->no;
	osEventFlagsSet(polling_evt_id, 0x0001);
}

