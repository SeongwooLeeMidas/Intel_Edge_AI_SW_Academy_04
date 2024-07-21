/*
 * io.c
 *
 *  Created on: Apr 11, 2024
 *      Author: iot00
 */


// EXTI : external interrupt > 외부에서 온 interrupt

#include <stdbool.h>
#include "io.h"

extern UART_HandleTypeDef huart3;

//int __io_putchar(int ch)
//{
//	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xffff);
//	return ch;
//}

int _write(int file, char *ptr, int len)
{
  (void)file;
  //int DataIdx;

  HAL_UART_Transmit(&huart3, (uint8_t *)ptr, len, 0xffff);

  return len;
}
