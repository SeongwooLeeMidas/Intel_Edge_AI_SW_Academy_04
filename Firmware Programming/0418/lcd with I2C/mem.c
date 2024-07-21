/*
 * mem.c
 *
 *  Created on: Apr 16, 2024
 *      Author: iot00
 */

#include <stdbool.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "mem.h"


// Memory Pool�̶�?
/* 	OS�� ���ִ� malloc �Լ�
 * 	����� ���� �� ���� �� �ִ� Ǯ�� ����� �ΰ� ����� �ʿ��� ������ �־��� ���� ��.
 *
 * malloc�̶� ���� �ٸ��淡?
 * 		malloc�� �޸� �뷮�� ���ڶ�� �ƿ� �Ҵ��� ���� ����!
 * 		�׷��� memory pool�� OS�� �ϴϱ� �뷮�� ���ڶ��
 * 		����� ������ ��ٷȴٰ� ����
 * 	- ������ ũ��θ� �Ҵ��� �Ѵٴ� Ư¡�� ����
 * 		���� ������?	�޸� ����ȭ (fragmentation)�� �Ͼ�� �ʵ��� ��
 * 				���?	������ ũ��(block)�θ� �Ҵ��� �ϴϱ�
 * 						�� ĭ�� �� ���ٰ� �˷��ָ� ��� ������ ĭ���� ����� �ؼ�
 * 						�ٽ� ��Ȱ���ϱ� ���� *
 * 						���߿� Ǯ�� ��ȯ�� �� Ǯ ��ü�� ��ȯ�ع����⵵ ��
 *
 * 				�����ڵ� ��� ������ �Ҵ�Ǿ������ϱ� �˱Ⱑ ���� (��, ������� �豸��)
 * */


#define D_MEM_COUNT_MAX		10

// �޸� Ǯ�� ��ǥ�� ����������
static osMemoryPoolId_t mem_id = NULL;


// �޸𸮿� Pool�� RAM�� ������ ��� ������ٰ� �˷��ִ� �Լ�
void mem_init(void)
{

	mem_id = osMemoryPoolNew(D_MEM_COUNT_MAX, sizeof(MEM_T), NULL);
	// MEM_T mem_id[D_MEM_COUNT_MAX]�� malloc
	if (mem_id != NULL) printf("Memory Pool Created...\\n");
	else {
		printf("Memory Pool Create Fail...\r\n");
		while (1);
	}
}

// �Ʒ��� ���� ISR���� ���� ��,
// �޸�Ǯ�� ����� ���� ������ ���� ������ ������ ����ϴ� ���� ���� ����� ���ϴ� ��
// ���α׷� ��ü�� ������� �� �����ϱ�
// Timeout is always 0, when mem_alloc is called in ISR.

// �޸𸮿� Pool�� MEM_T ����ü�� �Ҵ��� �� �ִٸ� �ְ� ����ü�� ��ȯ����
MEM_T *mem_alloc(uint16_t size, uint32_t timeout)
{
	MEM_T *pMem = NULL;

	pMem = osMemoryPoolAlloc(mem_id, timeout);
	if (pMem == NULL) return NULL;
	pMem->id = mem_id;
	return pMem;
}

// �Է� ���� ����� ����� �Լ�
bool mem_free(MEM_T *pMem)
{
	 osMemoryPoolId_t id;
	 if (pMem == NULL) return false;
	 if (pMem->id == NULL) return false;
	 id = pMem->id;
	 pMem->id = NULL;
	 osMemoryPoolFree(id, pMem);
	 return true;
 }
