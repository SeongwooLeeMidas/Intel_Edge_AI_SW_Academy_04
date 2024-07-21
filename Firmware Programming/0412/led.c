/*
 * led.c
 *
 *  Created on: Apr 12, 2024
 *      Author: IOT
 */

#include "main.h"
#include "led.h"

#define PORTB_BASE		0x40020400
#define BSRR_OFFSET		0x18

#define LED_MAX 3
const LED_T gLedObjs[LED_MAX] = {
		{PORTB_BASE + BSRR_OFFSET,		0,		0+16	},
		{PORTB_BASE + BSRR_OFFSET,		7, 		7+16	},
		{PORTB_BASE + BSRR_OFFSET,		14,		14+16	}
};


// Each LED pin numbers are 0, 7, 14
void led_onoff(int led_num, int onoff){

	int pin;
	uint32_t bit;

	if(onoff != 0)	pin = gLedObjs[led_num-1].on;
	else 			pin = gLedObjs[led_num-1].off;

	bit = (0x1 << (pin));

	*(uint32_t *)(PORTB_BASE + BSRR_OFFSET) |= bit;
}
