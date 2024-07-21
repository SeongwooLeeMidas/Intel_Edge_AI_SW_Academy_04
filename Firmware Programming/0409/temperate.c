/*
 * button.c
 *
 *  Created on: Apr 9, 2024
 *      Author: IOT
 */
#include 	"main.h"
#include	"temperate.h"


static TEMPERATE_T gBtnObjs[] = {
		{NULL,	0,	3000,	0,		temperate_dummy,	{0, 0}	},
		{NULL, 	0,	0,  	0,		NULL,				{0, 0}	}
};

void temperate_init(void){

}

void temperate_regcbf(uint16_t idx, FUNC_CBF cbf){
	gBtnObjs[idx].cbf = cbf;
}

void temperate_regBorder(uint16_t idx, uint16_t border){
	gBtnObjs[idx].sts.border = border;
}

void temperate_check(void){
	TEMPERATE_T *p = &gBtnObjs[0];

	// 배열에 저장되어있는 버튼들의 정보 모두 갱신
	for(uint8_t i = 0; p->cbf != NULL;i++){
		// 외부에서 해당 함수의 호출을 일정 틱마다 해준다는 전제하에 작성한 코드

		p->count++;
		p->count %= p->period;

		if(p->count == 0){
			// 값을 불러오는 부분: 온도 같은거는
			p->sts.state = rand()%65536;
			p->cbf((void *)&(p->sts));
		}
		p++;
	}
}

static void temperate_dummy(void*){
	return;
}
