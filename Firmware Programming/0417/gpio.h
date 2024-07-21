/*
 * gpio.h
 *
 *  Created on: Apr 15, 2024
 *      Author: IOT
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include <stdbool.h>
#include "main.h"


typedef void (*IO_CBF_T)(uint8_t, void *);
typedef struct {
	GPIO_TypeDef *port;			// GPIO Port
	uint16_t pin;					// GPIO Pin
	IO_CBF_T cbf;
} IO_EXTI_T;


#ifdef __cplusplus
extern "C" {
#endif


void io_exti_init(void);
bool io_exti_regcbf(uint8_t idx, IO_CBF_T cbf);


#ifdef __cplusplus
}
#endif

#endif /* INC_GPIO_H_ */
