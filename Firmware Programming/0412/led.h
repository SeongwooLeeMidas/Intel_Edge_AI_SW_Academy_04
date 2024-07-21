/*
 * led.h
 *
 *  Created on: Apr 12, 2024
 *      Author: IOT
 */

#ifndef INC_LED_H_
#define INC_LED_H_


typedef struct{
	uint32_t bsrr_addr;
	uint16_t on, off;
} LED_T;


#ifdef __cplusplus
extern "C"{
#endif


void led_onoff(int led_num, int onoff);


#ifdef __cplusplus
}
#endif

#endif /* INC_LED_H_ */
