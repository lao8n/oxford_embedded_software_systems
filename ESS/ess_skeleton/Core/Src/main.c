/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ess_helper.h"
#include "led_driver.h"

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

	// Set up button press
	Button_t b;

	button_init(&b, GPIOA->IDR);
	led_init(&led, port, led_blue_pin);
	button_loop(&b, &led);
}
