/*
 * button.h
 *
 *  Created on: Apr 11, 2024
 *      Author: iot00
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include <stdbool.h>


typedef void (*BUTTON_CBF)(void *arg);
typedef struct {
	uint8_t edge; 		// rising = 1, falling = 0
	uint16_t no;		// button number
	BUTTON_CBF cbf;

	uint32_t prev_tick;
} BUTTON_T;


enum{
	E_BTN_BLUE,
	E_BTN_UART,
	E_BTN_MAX
};


#ifdef __cplusplus
extern "C" {
#endif


void button_init(void);
bool button_regcbf(uint16_t idx, BUTTON_CBF cbf);
void button_proc_blue(void *);
void button_proc_uart(void *);


#ifdef __cplusplus
}
#endif

#endif /* INC_BUTTON_H_ */
