/*
 * slip.c
 *
 *  Created on: Apr 17, 2024
 *      Author: IOT
 */

#include <stdio.h>
#include "type.h"
#include "mem.h"
#include "slip.h"


#define FEND 0xC0
#define FESC 0xDB
#define TFEND 0xDC
#define TFESC 0xDD

void  slip_decode(uint8_t *state, uint8_t rxd, BUF_T *p, UART_CBF cbf) {

	switch(*state){
		case 0:{
			if(rxd == FEND){
				*state += 1;
				p->idx = 0;
			}
		} break;

		case 1: {
			if(rxd == FEND){
				if(p->idx == 0)	*state = 0;
				else{
					p->flag = true;
					if (cbf != NULL)
						cbf((void *)p); 	//&gBufObjs[E_UART_1]);
					p->flag = false;
					*state = 0;
				}
			}
			else if (rxd == FESC) { *state += 1;}
			else { p->buf[p->idx++] = rxd; }
		} break;

		case 2:{
			if (rxd == TFEND)	{
				p->buf[p->idx++] = FEND;
				*state -= 1;
			}
			else if (rxd == TFESC)	{
				p->buf[p->idx++] = FESC;
				*state -= 1;
			}
			else  		*state = 0;
		} break;
	}
}


bool slip_encode(const uint8_t *pRaw, uint16_t rawLen, uint8_t *pEncode, uint16_t *pEncodeLen)
{
	if (pRaw == NULL || pEncode == NULL || pEncodeLen == NULL) return false;

	uint16_t idx = 0;

	pEncode[idx++] = FEND;
	for (uint16_t i=0; i<rawLen; i++) {
		if (pRaw[i] == FEND) {
			pEncode[idx++] = FESC;
			pEncode[idx++] = TFEND;
		} else if (pRaw[i] == FESC) {
			pEncode[idx++] = FESC;
			pEncode[idx++] = TFESC;
		} else {
			pEncode[idx++] = pRaw[i];
		}
	}
	pEncode[idx++] = FEND;

	pEncodeLen[0] = idx;  // *pEncodeLen = idx;

	return true;
}
