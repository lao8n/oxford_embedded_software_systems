#include "acc.h"

void AccInit(void){
	SPIAcc_Init();
	uint8_t buffer[1];
	SPIAcc_Get(0x0F, buffer, 1); // WHOAMI
	// set fastest sampling rate
	buffer[1] = 0x87;
	SPIAcc_Send(20, buffer, 1); // CTRL_REG1
}

void AccRead(acc3_t * reading){
	uint8_t data[6];
	SPIAcc_Get(0x28, data, 2); // OUT_X_L, OUT_X_H;
	SPIAcc_Get(0x2A, &data[2], 2); // OUT_Y_L, OUT_Y_H;
	SPIAcc_Get(0x2C, &data[4], 2); // OUT_Z_L, OUT_Z_H;
	int16_t x_axis = (data[1] << 8) + data[0];
	int16_t y_axis = (data[3] << 8) + data[2];
	int16_t z_axis = (data[5] << 8) + data[4];
	reading->x = x_axis;
	reading->y = y_axis;
	reading->z = z_axis;
}
