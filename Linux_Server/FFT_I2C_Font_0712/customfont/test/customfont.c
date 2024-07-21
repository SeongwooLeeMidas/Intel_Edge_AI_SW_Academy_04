// lcd custom font1
I2C_CLCD_SendByte(0, 0x40);
I2C_CLCD_SendByte(1, 0b10000);
I2C_CLCD_SendByte(1, 0b01000);
I2C_CLCD_SendByte(1, 0b00100);
I2C_CLCD_SendByte(1, 0b00010);
I2C_CLCD_SendByte(1, 0b00010);
I2C_CLCD_SendByte(1, 0b00100);
I2C_CLCD_SendByte(1, 0b01000);
I2C_CLCD_SendByte(1, 0b10000);

I2C_CLCD_SendByte(1, 0b10000);
I2C_CLCD_SendByte(1, 0b01000);
I2C_CLCD_SendByte(1, 0b00100);
I2C_CLCD_SendByte(1, 0b00010);
I2C_CLCD_SendByte(1, 0b00010);
I2C_CLCD_SendByte(1, 0b00100);
I2C_CLCD_SendByte(1, 0b01000);
I2C_CLCD_SendByte(1, 0b10000);
I2C_CLCD_GotoXY(0, 0);
I2C_CLCD_PutC(0);
while (1);
//*/

// lcd custom font2
I2C_CLCD_CustomFont();
I2C_CLCD_GotoXY(0, 0);
I2C_CLCD_PutC(0);
I2C_CLCD_PutC(1);
I2C_CLCD_PutC(2);
I2C_CLCD_PutC(3);
I2C_CLCD_PutC(4);
I2C_CLCD_PutC(5);
while (1);
//*/

// lcd custom font3
I2C_CLCD_CustomFont();
for (int i = 0; i < 81; i++) {
	I2C_CLCD_Progressbar(i, 0);
	HAL_Delay(50);
}
while (1);

// lcd custom font4
I2C_CLCD_CustomFontV();
I2C_CLCD_GotoXY(0, 0);
I2C_CLCD_PutC(0);
I2C_CLCD_PutC(1);
I2C_CLCD_PutC(2);
I2C_CLCD_PutC(3);
I2C_CLCD_PutC(4);
I2C_CLCD_PutC(5);

while (1);