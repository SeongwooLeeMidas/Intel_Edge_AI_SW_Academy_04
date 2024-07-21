/*
 * io.h
 *
 *  Created on: Mar 29, 2024
 *      Author: IOT
 */

#ifndef SRC_IO_H_
#define SRC_IO_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C"{
#endif

int __ioputchar(int ch);

void led_toggle(int led_num, bool flag);

void led_onoff(int port, int pin, bool flag);

void led_on(int pin);
void led_off(int pin);

void led1_on(void);
void led1_off(void);
void led2_on(void);
void led2_off(void);
void led3_on(void);
void led3_off(void);

#ifdef __cplusplus
}

#endif

#endif /* SRC_IO_H_ */
