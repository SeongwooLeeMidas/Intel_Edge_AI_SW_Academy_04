/*
 * timer.h
 *
 *  Created on: Apr 12, 2024
 *      Author: IOT
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"

#ifdef __cplusplus
extern "C"{
#endif


void timer_init(void);
void timer_thread(void* arg);
void tim_duty_set(uint16_t duty);



#ifdef __cplusplus
}
#endif

#endif /* INC_TIMER_H_ */
