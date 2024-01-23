/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ess_helper.h"
#include "led_driver.h"
#include "stdio.h"

int _write(int file, char *ptr, int len){
	int i = 0;
	for(i = 0; i < len; i++){
		ITM_SendChar((*ptr++));
	}
	return len;
}

int main(void)
{
	/* Initialize system */
	HAL_Init();
	/* Initialize peripherals on board */
	ess_helper_init();

	LED_t led;
	uint32_t * port = (uint32_t*) 0x40020C14;
	uint32_t led_green_pin=0;
	uint32_t led_red_pin=1;
	uint32_t led_orange_pin=2;
	uint32_t led_blue_pin=3;
	printf("LED Red is on");

	// Set all the LEDs to on.
	led_init(&led, port, led_green_pin);
	led_on(&led);
	delay_msec(1000);
	led_off(&led);
	led_init(&led, port, led_red_pin);
	led_on(&led);
	delay_msec(1000);
	led_off(&led);
	led_init(&led, port, led_orange_pin);
	led_on(&led);
	delay_msec(1000);
	led_off(&led);
	led_init(&led, port, led_blue_pin);
	led_on(&led);
	delay_msec(1000);
	led_off(&led);
	printf("LED Green is on");

	// Set up button press
	while(1){
		if(GPIOA->IDR & 0x1){
			led_on(&led);
			delay_msec(1000);
		} else {
			led_off(&led);
			delay_msec(1000);
		}
	}

}
