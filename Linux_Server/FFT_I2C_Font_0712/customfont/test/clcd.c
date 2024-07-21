void I2C_CLCD_CustomFontV() {
	I2C_CLCD_SendByte(0, 0x40);
	for (int i = 0; i < 8; i++)	// PutC(0)
		I2C_CLCD_SendByte(1, 0b00000);
	for (int i = 0; i < 8; i++)	// PutC(1)
		I2C_CLCD_SendByte(1, i == 7 ? 0b00000 : 0b11111);
	for (int i = 0; i < 8; i++)	// PutC(2)
		I2C_CLCD_SendByte(1, i == 6 ? 0b00000 : 0b11111);
	for (int i = 0; i < 8; i++)
		I2C_CLCD_SendByte(1, i == 5 ? 0b00000 : 0b11111);
	for (int i = 0; i < 8; i++)
		I2C_CLCD_SendByte(1, i == 4 ? 0b00000 : 0b11111);
	for (int i = 0; i < 8; i++)
		I2C_CLCD_SendByte(1, i == 3 ? 0b00000 : 0b11111);
	for (int i = 0; i < 8; i++)
		I2C_CLCD_SendByte(1, i == 2 ? 0b00000 : 0b11111);
	for (int i = 0; i < 8; i++)
		I2C_CLCD_SendByte(1, i == 1 ? 0b00000 : 0b11111);
	for (int i = 0; i < 8; i++)
		I2C_CLCD_SendByte(1, i == 0 ? 0b00000 : 0b11111);
}