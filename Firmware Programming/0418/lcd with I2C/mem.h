/*
 * mem.h
 *
 *  Created on: Apr 16, 2024
 *      Author: iot00
 */

#ifndef INC_MEM_H_
#define INC_MEM_H_

#include <stdbool.h>

// const로 생성하면 안됨
// 메모리는 풀에서 할당을 하니까 굳이 생성 필요없이 풀에서 더 만들 수 있음
typedef struct {
	osMemoryPoolId_t id;
	uint8_t buf[100+1];
} MEM_T;

#ifdef __cplusplus
extern "C" {
#endif

void mem_init(void);
MEM_T *mem_alloc(uint16_t size, uint32_t timeout);
bool mem_free(MEM_T *pMem);

#ifdef __cplusplus
}
#endif

#endif /* INC_MEM_H_ */
