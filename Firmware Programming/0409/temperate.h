/*
 * button.h
 *
 *  Created on: Apr 9, 2024
 *      Author: IOT
 */

#ifndef INC_TEMPERATE_H_
#define INC_TEMPERATE_H_

#include <stdbool.h>
#include <stdlib.h>

static void temperate_dummy(void*);	// 함수 포인터 오류 방지용
typedef void (*FUNC_CBF)(void*);	// 버튼이 눌리거나 떨어졌을때 이벤트 처리기


typedef struct{
	uint16_t border;			// 0도 기준점
	uint16_t state;				// 온도계 상태 return용
} TEMPERATE_STS;


typedef struct{
	GPIO_TypeDef *port;	// 버튼의 포트
	uint16_t pin;			// 버튼의 핀
	uint32_t period, count;		// 측정 주기, 현재가 몇 쯔음인지
	FUNC_CBF cbf;				// 이벤트 처리 함수 포인터
	TEMPERATE_STS sts;			// 온도계의 상태 저장
} TEMPERATE_T;


#ifdef __cplusplus
extern "C"{
#endif

void temperate_init(void);								// 버튼 초기화 함수
void temperate_regcbf(uint16_t idx, FUNC_CBF cbf);		// 이벤트 처리기 설정
void temperate_regBorder(uint16_t idx, uint16_t border);
void temperate_check(void);								// 버튼의 정보 갱신 및 이벤트 생성

#ifdef __cplusplus
}
#endif

#endif /* INC_TEMPERATE_H_ */
