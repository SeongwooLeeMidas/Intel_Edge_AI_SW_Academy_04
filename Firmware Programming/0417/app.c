/*
 * app.c
 *
 *  Created on: Apr 11, 2024
 *      Author: iot00
 */
#include <stdio.h>
#include "cmsis_os.h"
#include "mem.h"
#include "io.h"
#include "uart.h"
#include "cli.h"
#include "gpio.h"
#include "polling.h"
#include "app.h"

static void app_init(void);

void app(void)
{
	osKernelInitialize();
	app_init();
	osKernelStart();
}

static void app_init(void)
{
	mem_init();
	io_exti_init();
	uart_init();

	cli_init();
	polling_init();
	cmd_init();
}



