/*
 * softtimer.c
 *
 *  Created on: Apr 18, 2024
 *      Author: IOT
 */

#include <stdio.h>
#include "cmsis_os.h"

static osTimerId_t timer_hnd;

static void periodic_func(void*);
void (*timer_cbf)(void);

// 유틸리치에 해당하는 함수
void softtimer_init(void)
{
	/*
	 * 인자 1: 함수 포인터
	 * 인자 2: osTimerOnce - 1번 실행 / osTimerperiodic - 여러번 실행
	 * 인자 3: 함수 인자
	 * 인자 4:
	 * */
	timer_hnd = osTimerNew(periodic_func, osTimerPeriodic, NULL, NULL);
	if (timer_hnd != NULL) {
		printf("Soft Timer Created...\r\n");
	} else {
		printf("Soft Timer Create Fail...\r\n");
		while (1);
	}
}


void softtimer_start(uint32_t ticks){

	osTimerStart(timer_hnd, ticks);
}


void softtimer_stop(void)
{
	osTimerStop(timer_hnd);
}


void softtimer_regcbf(void (*cbf)(void)){

	timer_cbf = cbf;
}




static void periodic_func(void *arg){

	(void)arg;

	if (timer_cbf != NULL) timer_cbf();
}
