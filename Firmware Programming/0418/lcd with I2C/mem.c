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


// Memory Pool이란?
/* 	OS가 해주는 malloc 함수
 * 	블록을 여러 개 넣을 수 있는 풀을 만들어 두고 블록은 필요할 때마다 넣었다 뺏다 함.
 *
 * malloc이랑 뭐가 다르길래?
 * 		malloc은 메모리 용량이 모자라면 아예 할당을 하지 않음!
 * 		그런데 memory pool은 OS가 하니까 용량이 모자라면
 * 		블록이 빠지길 기다렸다가 해줌
 * 	- 정해진 크기로만 할당을 한다는 특징이 있음
 * 		뭐가 좋은데?	메모리 파편화 (fragmentation)이 일어나지 않도록 함
 * 				어떻게?	동일한 크기(block)로만 할당을 하니까
 * 						그 칸을 안 쓴다고만 알려주면 사용 가능한 칸으로 기억을 해서
 * 						다시 재활용하기 쉬움 *
 * 						나중에 풀을 반환할 때 풀 전체를 반환해버리기도 함
 *
 * 				관리자도 블록 단위로 할당되어있으니까 알기가 쉬움 (아, 여기까지 썼구나)
 * */


#define D_MEM_COUNT_MAX		10

// 메모리 풀의 좌표는 전역변수로
static osMemoryPoolId_t mem_id = NULL;


// 메모리에 Pool를 RAM에 공간을 잡고 만들었다고 알려주는 함수
void mem_init(void)
{

	mem_id = osMemoryPoolNew(D_MEM_COUNT_MAX, sizeof(MEM_T), NULL);
	// MEM_T mem_id[D_MEM_COUNT_MAX]를 malloc
	if (mem_id != NULL) printf("Memory Pool Created...\\n");
	else {
		printf("Memory Pool Create Fail...\r\n");
		while (1);
	}
}

// 아래의 말은 ISR에서 접근 시,
// 메모리풀에 블록을 넣을 공간을 잡을 때까지 무한히 대기하는 것을 하지 말라고 말하는 것
// 프로그램 전체가 멈춰버릴 수 있으니까
// Timeout is always 0, when mem_alloc is called in ISR.

// 메모리에 Pool에 MEM_T 구조체를 할당할 수 있다면 넣고 구조체를 반환해줌
MEM_T *mem_alloc(uint16_t size, uint32_t timeout)
{
	MEM_T *pMem = NULL;

	pMem = osMemoryPoolAlloc(mem_id, timeout);
	if (pMem == NULL) return NULL;
	pMem->id = mem_id;
	return pMem;
}

// 입력 받은 블록을 빼라는 함수
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
