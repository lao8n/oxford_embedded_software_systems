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

#define PORTD ((uint32_t*)0x40020C14)

int _write(int file, char *ptr, int len){
	int i = 0;
	for(i = 0; i < len; i++){
		ITM_SendChar((*ptr++));
	}
	return len;
}

int main(void){
	// create led adts
	LED_t led_green;
	LED_t led_orange;
	LED_t led_blue;
	LED_t led_red;

	/* Initialize system */
	HAL_Init();
	/* Initialize peripherals on board */
	ess_helper_init();

	// set up the leds
	led_init(&led_green, PORTD, GREEN);
	led_init(&led_orange, PORTD, ORANGE);
	led_init(&led_blue, PORTD, BLUE);
	led_init(&led_red, PORTD, RED);

	// set up pwm driver
	pwm_driver_init(&led_green, &led_red, &led_orange, &led_blue);

	// set brightness values
	pwm_driver_set(GREEN, 0);
	pwm_driver_set(ORANGE, 0);
	pwm_driver_set(BLUE, 0);
	pwm_driver_set(RED, 0);

	SPIAcc_Init();
	TMR4_Init_ISR();

	uint8_t buffer[1];
	SPIAcc_Get(0x0F, buffer, 1); // WHOAMI
	// set fastest sampling rate
	buffer[1] = 0x87;
	SPIAcc_Send(20, buffer, 1); // CTRL_REG1

	// loop
	while(1){
		uint8_t x_data[2];
		SPIAcc_Get(0x28, x_data, 2); // OUT_X_L, OUT_X_H;
		int16_t x_axis = (x_data[1] << 8) + x_data[0];
		if(x_axis < -2000) {
			pwm_driver_set(GREEN, 100);
			pwm_driver_set(RED, 0);
		} else if (x_axis > 2000) {
			pwm_driver_set(RED, 100);
			pwm_driver_set(GREEN, 0);
		} else if (x_axis < -1000){
			// -1000 to -2000 go from 0 to 100 in brightness
			// -1000 -> 0 brightness
			// -2000 -> 1 brightness
			uint8_t brightness = (x_axis + 1000)/-10;
			pwm_driver_set(GREEN, brightness);
			pwm_driver_set(RED, 0);
		} else if (x_axis > 1000){
			// 1000 to 2000 go from 0 to 100 in brightness
			// 1000 -> 0 brightness
			// 2000 -> 100 brightness
			uint8_t brightness = (x_axis - 1000)/10;
			pwm_driver_set(RED, brightness);
			pwm_driver_set(GREEN, 0);
		} else {
			pwm_driver_set(RED, 0);
			pwm_driver_set(GREEN, 0);
		}
	};
}
