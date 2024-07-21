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
#include "uart.h"

void app_init(void);

void app(void)
{
	printf("System Started.....!\r\n");

	app_init();

	while (1) {
		// 이곳에 adc가 없는 이유는 polling의 하단으로 포함되어 숨었기 때문

		polling_thread(NULL);
		button_thread(NULL);
		uart_thread(NULL);
	}
}

void app_init(void)
{
	io_exti_init();
	polling_init();
	button_init();
	uart_init();
}
