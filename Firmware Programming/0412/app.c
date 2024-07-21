/*
 * app.c
 *
 *  Created on: Apr 11, 2024
 *      Author: iot00
 */
#include <stdio.h>
#include "io.h"
#include "polling.h"
#include "button.h"
#include "app.h"
#include "cli.h"
#include "uart.h"
#include "timer.h"

void app_init(void);
void app_mode(int mode);

// 내부용 함수라 헤더에 필요 없음
static void app_normal(void);
static void app_diagnostic(void);

// 내부에서만 쓸 함수 포인터
static void (*mode_func)(void);



void app(void)
{
	printf("System Started!\r\n");

	mode_func = app_diagnostic;
	app_init();

	while (1) {
		mode_func();
	}
}


void app_init(void)
{
	io_exti_init();
	polling_init();
	button_init();
	uart_init();
	cli_init();
	timer_init();

}


static void app_normal(void){

	polling_thread(NULL);
	button_thread(NULL);
	uart_thread(NULL);
	cli_thread(NULL);
	timer_thread(NULL);
}

static void app_diagnostic(void){

	uart_thread(NULL);
	cli_thread(NULL);
	timer_thread(NULL);
}


void app_mode(int mode)
{
	if (mode == 0) {
		printf("\nMode : Normal \r\n");
		mode_func = app_normal;
	} else {
		printf("\nMode : Diagnostic \r\n");
		mode_func = app_diagnostic;
	}
}
