void writeI2C(uint16_t address, uint8_t data) {
	uint8_t txBuffer[3];
	txBuffer[0] = address >> 8;
	txBuffer[1] = address;
	txBuffer[2] = data;
	HAL_I2C_Master_Transmit(&hi2c1, 0x27, txBuffer, sizeof(txBuffer), 1);
}

void readI2C(uint16_t address) {
	uint8_t txBuffer[2];
	uint8_t txBuffer[1];
	txBuffer[0] = address >> 8;
	txBuffer[1] = address;
	HAL_I2C_Master_Transmit(&hi2c1, 0x4e >> 1, txBuffer, sizeof(txBuffer), 1);
	HAL_I2C_Master_Receive(&hi2c1, 0x4e >> 1, rxBuffer, sizeof(rxBuffer), 1);
	return rxBuffer[0];
}

// 쉬운 version code로 변경
//void writeI2C(uint16_t address, uint8_t data) {
//	HAL_I2C_Mem_Write(&hi2c1, 0x27, adress, 2, &data, 1, 1);
//}
//
//void readI2C(uint16_t address) {
//	uint8_t result;
//	HAL_I2C_Mem_Read(&hi2c1, 0x27, address, 2, &result, 1, 1);
//	return result;
//}