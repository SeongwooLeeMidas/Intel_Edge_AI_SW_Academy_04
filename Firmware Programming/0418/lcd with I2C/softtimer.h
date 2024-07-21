/*
 * softtimer.h
 *
 *  Created on: Apr 18, 2024
 *      Author: IOT
 */

#ifndef INC_SOFTTIMER_H_
#define INC_SOFTTIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

void softtimer_init(void);
void softtimer_start(uint32_t ticks);
void softtimer_stop(void);
void softtimer_regcbf(void (*cbf)(void));


#ifdef __cplusplus
}
#endif

#endif /* INC_SOFTTIMER_H_ */
