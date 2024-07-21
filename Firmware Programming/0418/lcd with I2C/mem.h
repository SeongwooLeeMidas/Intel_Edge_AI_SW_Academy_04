/*
 * mem.h
 *
 *  Created on: Apr 16, 2024
 *      Author: iot00
 */

#ifndef INC_MEM_H_
#define INC_MEM_H_

#include <stdbool.h>

// const�� �����ϸ� �ȵ�
// �޸𸮴� Ǯ���� �Ҵ��� �ϴϱ� ���� ���� �ʿ���� Ǯ���� �� ���� �� ����
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
