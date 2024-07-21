/*
 * button.c
 *
 *  Created on: Apr 9, 2024
 *      Author: iot00
 */

#include <stdio.h>
#include "button.h"

static void button_dummy(void *);

static BUTTON_T gBtnObjs[] = {
	{ USER_Btn_GPIO_Port, 	USER_Btn_Pin, 	80, 	0, 		0, 	0,		button_dummy, 	{ true, 	0 	}},
	{ NULL, 		0, 		0,	0,		0,	0,		NULL,		{ true, 	0	}}
};

void button_init(void)
{

}

void button_regcbf(uint16_t idx, FUNC_CBF cbf)
{
	gBtnObjs[idx].cbf = cbf;
}

void button_check(void)
{
	BUTTON_T *p = &gBtnObjs[0];

	for (uint8_t i=0; p->cbf != NULL; i++) {
		p->count++;
		p->count %= p->period;

		//gBtnObjs[i].count++;
		//gBtnObjs[i].count %= gBtnObjs[i].period;
		//p[i].count++;
		//p[i].count %= p[i].period;
		//if (p->count > p->period) p->count = 0;

		if (p->count == 0) {
			p->curr =	HAL_GPIO_ReadPin(p->port, p->pin);
			if (p->prev == 0 && p->curr == 1) {  // rising
				p->sts.edge = true;
				//p->sts.pushed_count = 0;
				p->cbf((void *)&(p->sts)); // == button_callback((void *)&gBtnObj[i].sts);
			} else if (p->prev == 1 && p->curr == 0) {	// falling
				p->sts.edge = false;
				p->cbf((void *)&(p->sts));
			} else if (p->prev == 1 && p->curr == 1) {	// pushing
				if (p->sts.pushed_count < 100) p->sts.pushed_count++;
			} else {  // released
				p->sts.pushed_count = 0;
			}
			p->prev = p->curr;
		}

		p++; // p = p+1;
	}
}

static void button_dummy(void *)
{
	printf("I'm dummy\r\n");
	return;
}
