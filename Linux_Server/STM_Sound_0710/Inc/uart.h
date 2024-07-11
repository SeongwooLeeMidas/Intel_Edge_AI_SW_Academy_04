/*
 * uart.h
 *
 *  Created on: Jul 10, 2024
 *      Author: IOT
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

void initUart(UART_HandleTypeDef *inHandle);
char *getString();
void putSerial(int inValue);
void putSerial2(int inValue);

#endif /* INC_UART_H_ */
