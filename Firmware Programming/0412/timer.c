/*
 * timer.c
 *
 *  Created on: Apr 12, 2024
 *      Author: IOT
 */
#include "timer.h"

extern TIM_HandleTypeDef htim3;



void timer_init(void){

	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

void timer_thread(void* arg){

}


void tim_duty_set(uint16_t duty){

	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, duty);
}
