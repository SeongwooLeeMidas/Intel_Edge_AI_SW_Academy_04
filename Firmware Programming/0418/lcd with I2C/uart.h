/*
 * uart.h
 *
 *  Created on: Apr 11, 2024
 *      Author: iot00
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

typedef void (*UART_CBF)(void *);

enum {
	E_UART_0,		// uart2
	E_UART_1,		// uart3
	E_UART_MAX
};

#ifdef __cplusplus
extern "C" {
#endif

void uart_init(void);
bool uart_regcbf(uint8_t idx, UART_CBF cbf);
bool slip_encode(const uint8_t *pRaw, uint16_t rawLen, uint8_t *pEncode, uint16_t *pEncodeLen);

#ifdef __cplusplus
}
#endif

#endif /* SRC_UART_H_ */
