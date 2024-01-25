/* Includes ------------------------------------------------------------------*/
#include "ess_helper.h"
#include "led_driver.h"
#include "stdio.h"
#include "delay.h"
#include "stm32f4xx.h"
#include "pwm_driver.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "display_driver.h"
#include "spi_driver.h"

int _write(int file, char *ptr, int len){
	int i = 0;
	for(i = 0; i < len; i++){
		ITM_SendChar((*ptr++));
	}
	return len;
}

int main(void){
	/* Initialize system */
	HAL_Init();
	/* Initialize peripherals on board */
	ess_helper_init();

	display_init();

	SPIAcc_Init();
	TMR4_Init_ISR();

	uint8_t buffer[1];
	SPIAcc_Get(0x0F, buffer, 1); // WHOAMI
	// set fastest sampling rate
	buffer[1] = 0x87;
	SPIAcc_Send(20, buffer, 1); // CTRL_REG1

	// loop
	while(1){
		uint8_t data[6];
		SPIAcc_Get(0x28, data, 2); // OUT_X_L, OUT_X_H;
		SPIAcc_Get(0x2A, &data[2], 2); // OUT_Y_L, OUT_Y_H;
		SPIAcc_Get(0x2C, &data[4], 2); // OUT_Z_L, OUT_Z_H;
		int16_t x_axis = (data[1] << 8) + data[0];
		int16_t y_axis = (data[3] << 8) + data[2];
		display_axis(x_axis, GREEN, RED);
		display_axis(y_axis, ORANGE, BLUE);
	};
}
