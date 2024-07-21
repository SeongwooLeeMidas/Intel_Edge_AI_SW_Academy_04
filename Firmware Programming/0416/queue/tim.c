/*
 * tim.c
 *
 *  Created on: Apr 12, 2024
 *      Author: iot00
 */
#include "tim.h"

//extern TIM_HandleTypeDef htim3;

void tim_init(void)
{
	//HAL_TIM_Base_Start(&htim3);
	//HAL_TIM_PWM_Start(&htim3,  TIM_CHANNEL_3);
}

void tim_thread(void *arg)
{

}

void tim_duty_set(uint16_t duty)
{
	duty %= 1000;
	//__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, duty);
}
