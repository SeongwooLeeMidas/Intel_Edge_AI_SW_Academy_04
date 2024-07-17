// i2c test code
int lineNumber = 10;
for (int address = 0; address < 256; address++) {
	if (HAL_I2C_IsDeviceReady(&hi2c1, address, 0, 1) == HAL_OK) {
		char str[20];
		sprintf(str, "%d is ok", address);
		u8g2_DrawStr(&u8g2, 0, lineNumber, str);
		lineNumber += 10;
	}
}
u8g2_SendBuffer(&u8g2);
while (1);