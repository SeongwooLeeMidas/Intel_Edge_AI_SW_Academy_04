/*
 * button.h
 *
 *  Created on: Apr 9, 2024
 *      Author: iot00
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <stdbool.h>
#include "main.h"

typedef void (*FUNC_CBF)(void *);

typedef struct {
	bool edge;
	uint16_t pushed_count;
} BUTTON_STS;

typedef struct {
	GPIO_TypeDef *port;			// GPIO Port
	uint16_t pin;					// GPIO Pin
	uint32_t period, count;		// 얼마만에 한번 체크할 것이가?
	uint8_t prev, curr;
	FUNC_CBF cbf;	// callback function
	BUTTON_STS sts;
} BUTTON_T;

#ifdef __cplusplus
extern "C" {
#endif

void button_init(void);
void button_regcbf(uint16_t idx, FUNC_CBF cbf);
void button_check(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_BUTTON_H_ */
