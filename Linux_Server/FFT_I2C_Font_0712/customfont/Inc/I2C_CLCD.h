#ifndef I2C_CLCD_H_
#define I2C_CLCD_H_

/*
 * P0 P1 P2 P3 P4 P5 P6 P7
 * ��  ��  ��  ��  ��  ��  ��  ��
 * RS RW EN NC D4 D5 D6 D7
 */

/* Defines */

#define I2C_CLCD_RS		0
#define I2C_CLCD_RW		1
#define I2C_CLCD_E		2
#define I2C_CLCD_LED	3
#define I2C_CLCD_D4		4
#define I2C_CLCD_D5		5
#define I2C_CLCD_D6		6
#define I2C_CLCD_D7		7

#define WRITE		0x00
#define READ		0x01
#define PCF8574_AD	0x4e

/* Includes */

#include "main.h"

/* Functions */

uint8_t	I2C_CLCD_BusyFlag(void);
void	I2C_CLCD_Delay_us(uint8_t us);
void	I2C_CLCD_SendByte(uint8_t RS_State, uint8_t Byte);
void	I2C_CLCD_init(I2C_HandleTypeDef *hi2c);
void	I2C_CLCD_GotoXY(uint8_t X, uint8_t Y);
void	I2C_CLCD_PutC(uint8_t C);
void	I2C_CLCD_PutStr(uint8_t *Str);
void 	I2C_CLCD_Cursor(uint8_t on);
void  I2C_CLCD_Right();
void  I2C_CLCD_Left();
void 	I2C_CLCD_ShiftStop();
void 	I2C_CLCD_Progressbar(uint8_t n, uint8_t line);

#endif /* I2C_CLCD_H_ */
