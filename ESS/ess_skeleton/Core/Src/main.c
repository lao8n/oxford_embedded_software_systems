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
	pwm_driver_set(0, 0);
	pwm_driver_set(1, 25);
	pwm_driver_set(2, 50);
	pwm_driver_set(3, 100);

	TMR4_Init_ISR();
	TIM4_IRQHandler();

	SPIAcc_Init();
	uint8_t buffer[1];
	SPIAcc_Get(0x0F, buffer, 1);
	// loop
	while(1){};
}
