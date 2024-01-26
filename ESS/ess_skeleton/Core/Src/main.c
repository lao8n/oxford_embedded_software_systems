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
#include "acc.h"

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

	AccInit();
	TMR3_Init_ISR();
	TMR4_Init_ISR();
	acc3_t reading;
	// loop
	while(1){
		AccRead(&reading);
		display_axis(reading.x, GREEN, RED);
		display_axis(reading.y, ORANGE, BLUE);
	};
}
