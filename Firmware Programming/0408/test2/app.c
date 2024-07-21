/*
 * app.c
 *
 *  Created on: Apr 8, 2024
 *      Author: IOT
 */
#include <stdio.h>
#include "main.h"


void app(void)
{
	//uint16_t btn;
	//// Error!!!		GPIO_TypeDef *pPort = 0x40020800;
	//GPIO_TypeDef *pPort = GPIOC;	// (GPIO_TypeDef *)0x40020800;
	GPIO_PinState sts;

	printf("System start!\r\n");

	while(1){
		HAL_Delay(100);

		// btn = *(uint16_t *)0x40020810;		// Port C IDR
		//btn = pPort->IDR;

		//// 버튼 하나만 읽을
		//if(btn & (0x1 << 13)){
		//	printf("Blue button is pressed~\r\n");
		//}

		//sts = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
		sts = HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin);
		if(sts == GPIO_PIN_SET)
			printf("Blue button is pressed~\r\n");
	}
}
