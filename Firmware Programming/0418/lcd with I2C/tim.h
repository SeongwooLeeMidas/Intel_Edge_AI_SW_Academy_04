/*
 * tim.h
 *
 *  Created on: Apr 15, 2024
 *      Author: IOT
 */

#ifndef INC_TIM_H_
#define INC_TIM_H_

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void tim_init(void);
void tim_thread(void *arg);
void tim_duty_set(uint16_t duty);

#ifdef __cplusplus
}
#endif

#endif /* INC_TIM_H_ */
