/*
 * gpio.c
 *
 *  Created on: Apr 15, 2024
 *      Author: iot00
 */

// EXTI : external interrupt > �ܺο��� �� interrupt
#include "gpio.h"


//-----------------------------------------------

// EXTI�� 0~15���� �ְ� �� 16����
#define D_IO_EXTI_MAX		16
static IO_EXTI_T gIOExtiObjs[D_IO_EXTI_MAX];

static void io_exti_dummy(uint8_t rf, void *arg);

void io_exti_init(void)
{
	// �迭 ��ü �ӽ� �ʱ�ȭ
	for (int i=0; i<D_IO_EXTI_MAX; i++) {
		gIOExtiObjs[i].port = NULL;
		gIOExtiObjs[i].pin = 0;
		gIOExtiObjs[i].cbf = io_exti_dummy;
	}

	// �츮�� ����� ������ư�� 13���� �ʱ�ȭ
	gIOExtiObjs[13].port = USER_Btn_GPIO_Port;
	gIOExtiObjs[13].pin = USER_Btn_Pin;
}

// �ݹ��Լ��� �����ϱ� ���� �Լ� ����
bool io_exti_regcbf(uint8_t idx, IO_CBF_T cbf)
{
	if (idx > D_IO_EXTI_MAX) return false;
	gIOExtiObjs[idx].cbf = cbf;
	return true;
}

// �ܺο��� �� interrupt�� ���� ó���ϴ� �ݹ� �Լ�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	// ��ü 16�� �߿� ���° interrupt���� Ȯ���ϱ� ���� for��
	for (volatile uint16_t i=0; i<D_IO_EXTI_MAX; i++) {
		// ����Ǿ� �ִ� ��Ʈ�� ���� ������ �޾ƿ�
		volatile GPIO_PinState sts = HAL_GPIO_ReadPin(gIOExtiObjs[i].port, gIOExtiObjs[i].pin);
		// �ش� ���� ���� ���� �ɰ� �´ٸ�,
		// �� ��ġ�� �ݹ� ����� ȣ��
		if (GPIO_Pin & (0x01 << i)) 	gIOExtiObjs[i].cbf((uint8_t)sts, (void *)&i);
	}
}

// �ݹ� ����� ���� �������°� ������ ����
static void io_exti_dummy(uint8_t rf, void *arg)
{
	(void)rf;
	(void)arg;
}

