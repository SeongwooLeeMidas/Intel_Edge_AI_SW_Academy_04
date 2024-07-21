/*
 * io.c
 *
 *  Created on: Mar 29, 2024
 *      Author: IOT
 */
#include "main.h"
#include "io.h"

extern UART_HandleTypeDef huart3;
#define D_PRINTF_UART_HANDLE huart3

int __io_putchar(int ch){
	HAL_UART_Transmit(&D_PRINTF_UART_HANDLE, (uint8_t *)&ch, 1, 0xffff);
	return ch;
}


// PORTB_BASE + ODR_OFFSET = 0x40020414
#define PORTB_BASE		0x40020400
#define ODR_OFFSET		0x14
#define BSRR_OFFSET		0x18
#define LOCK_OFFSET		0x1C

typedef struct{
	uint32_t bsrr_addr;
	uint16_t on, off;
} LED_T;

#define LED_MAX 3
const LED_T gLedObjs[LED_MAX] = {
		{0x40020418,	0, 	0+16},
		{0x40020418,	7, 	7+16},
		{0x40020418,	14,	14+16}
};

void led_toggle(int led_num, bool flag){
	if(led_num > LED_MAX)	return;

	uint32_t bit = flag? (0x1 << gLedObjs[led_num].on) : (0x1 << gLedObjs[led_num].off);
	*(uint32_t *)gLedObjs[led_num].bsrr_addr = bit;
}


// Each LED pin numbers are 0, 7, 14
void led_onoff(int port, int pin, bool flag){
	uint32_t bit = flag? (0x1 << pin) : (0x1 << (pin+16));

	*(uint32_t *)(port + BSRR_OFFSET) |= bit;
}


// Each LED pin numbers are 0, 7, 14
void led_on(int pin){
	//*(uint32_t *)(PORTB_BASE + ODR_OFFSET) |= (0x1 << 0);			// == 0x0001
	*(uint32_t *)(PORTB_BASE + BSRR_OFFSET) |= (0x1 << pin);
}

// Each LED pin numbers are 0, 7, 14
void led_off(int pin){
	//*(uint32_t *)(PORTB_BASE + ODR_OFFSET) &= ~(0x1 << 0);			// == 0xfffe
	*(uint32_t *)(PORTB_BASE + BSRR_OFFSET) |= (0x1 << (16 + pin));
}



void led1_on(void){
	//*(uint32_t *)(PORTB_BASE + ODR_OFFSET) |= (0x1 << 0);			// == 0x0001
	*(uint32_t *)(PORTB_BASE + BSRR_OFFSET) |= (0x1 << 0);
}

void led1_off(void){
	//*(uint32_t *)(PORTB_BASE + ODR_OFFSET) &= ~(0x1 << 0);			// == 0xfffe
	*(uint32_t *)(PORTB_BASE + BSRR_OFFSET) |= (0x1 << 16);
}
