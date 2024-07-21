/*
 * disp.h
 *
 *  Created on: Apr 18, 2024
 *      Author: IOT
 */

#ifndef INC_DISP_H_
#define INC_DISP_H_


#include <stdio.h>
#include <stdarg.h>
#include "cmsis_os.h"
#include "i2c_HD44780.h"

#ifdef __cpluspluse
extern "C" {
#endif


void disp_init(void);
void disp_on(void);
void disp_off(void);
void disp_home(void);
void disp_clear_display(void);
void disp_locate(uint8_t row, uint8_t column);
void disp_printchar(unsigned char ascode);
void disp_print_string (char *str);
void disp_printf(const char *fmt, ...);


#ifdef __cplusplus
}
#endif

#endif /* INC_DISP_H_ */
