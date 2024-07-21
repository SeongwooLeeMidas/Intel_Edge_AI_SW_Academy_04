/*
 * uart.c
 *
 *  Created on: Jul 10, 2024
 *      Author: iot
 */

#include "uart.h"

#define STX 0x02
#define ETX 0x03

UART_HandleTypeDef *uartHandle;

uint8_t rxChar;
//for ring buffer
#define rxBufferMax 16
int rxReadPointer; // read pointer
int rxWritePointer; // write pointer
uint8_t rxBuffer[rxBufferMax]; //ring buffer

void initUart(UART_HandleTypeDef *inHandle){
	uartHandle=inHandle;
	HAL_UART_Receive_IT(uartHandle, &rxChar, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	rxBuffer[rxWritePointer++] = rxChar;
	rxWritePointer %= rxBufferMax;
	HAL_UART_Receive_IT(uartHandle, &rxChar, 1);
}

uint16_t getRxBuffer(){
	uint16_t result;
	if(rxWritePointer == rxReadPointer)return -1;
	result = rxBuffer[rxReadPointer++];
	rxReadPointer %= rxBufferMax;
	return result;
}

char *getString(){
	static char str[10];
	static uint8_t pos = 0;
	char ch = getRxBuffer();
	if(ch != -1) {
		if(ch == '\n'){
			memset(str, 0, 10);
			pos = 0;
		}
		else
			str[pos++] = ch;
	}
	return str;
}

void putSerial(int inValue){
	char txBuffer[5] = {0,};
	txBuffer[0] = STX;
	txBuffer[1] = (inValue & 0x7f) | 0x80;
	txBuffer[2] = (inValue >> 7 & 0x7f) | 0x80;
	txBuffer[3] = txBuffer[0] + txBuffer[1] + txBuffer[2];
	txBuffer[4] = ETX;
	HAL_UART_Transmit(uartHandle, txBuffer, 5, 1);
}
void putSerial2(int inValue){
	char txBuffer[4] = {0,};
	txBuffer[0] = 0x11;
	txBuffer[1] = 0x22;
//	txBuffer[3] = inValue;
//	txBuffer[4] = inValue >> 8;
	memcpy(&txBuffer[2], &inValue, 2);
	HAL_UART_Transmit(uartHandle, txBuffer, 4, 1);
}
