/*
 * usrt.h
 *
 *  Created on: Apr 11, 2024
 *      Author: IOT
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"


#define D_BUF_MAX			100
typedef struct {
  uint8_t buf[D_BUF_MAX+1]; // + '\0'
  uint8_t idx;	// count
  uint8_t flag;	// uart 를 통해 '\r' 이나 '\n' 받았을 경우
} BUF_T;


#ifdef __cplusplus
extern "C" {
#endif


void uart_init(void);
void uart_regcbf(void (*cbf)(void *));
void uart_thread(void *);


#ifdef __cplusplus
}
#endif

#endif /* SRC_UART_H_ */

