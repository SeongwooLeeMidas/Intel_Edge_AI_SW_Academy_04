/*
 * slip.h
 *
 *  Created on: Apr 17, 2024
 *      Author: IOT
 */

#ifndef INC_SLIP_H_
#define INC_SLIP_H_


#include "uart.h"


#ifdef __cplusplus
extern "C" {
#endif


void slip_decode(uint8_t *state, uint8_t rxd, BUF_T *buf, UART_CBF cbf);
bool slip_encode(const uint8_t *pRaw, uint16_t rawLen, uint8_t *pEncode, uint16_t *pEncodeLen);

#ifdef __cplusplus
}
#endif

#endif /* INC_SLIP_H_ */
