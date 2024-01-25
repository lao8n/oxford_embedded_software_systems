#include "display_driver.h"
#include "led_driver.h"
#include "pwm_driver.h"

#define PORTD ((uint32_t*)0x40020C14)


void display_init(void){
	// create led adts
	static LED_t led_green;
	static LED_t led_orange;
	static LED_t led_blue;
	static LED_t led_red;

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
}


void display_axis(int16_t axis, colour_t neg, colour_t pos){
	if(axis < -2000) {
		pwm_driver_set(neg, 100);
		pwm_driver_set(pos, 0);
	} else if (axis > 2000) {
		pwm_driver_set(pos, 100);
		pwm_driver_set(neg, 0);
	} else if (axis < -1000){
		// -1000 to -2000 go from 0 to 100 in brightness
		// -1000 -> 0 brightness
		// -2000 -> 1 brightness
		uint8_t brightness = (axis + 1000)/-10;
		pwm_driver_set(neg, brightness);
		pwm_driver_set(pos, 0);
	} else if (axis > 1000){
		// 1000 to 2000 go from 0 to 100 in brightness
		// 1000 -> 0 brightness
		// 2000 -> 100 brightness
		uint8_t brightness = (axis - 1000)/10;
		pwm_driver_set(pos, brightness);
		pwm_driver_set(neg, 0);
	} else {
		pwm_driver_set(pos, 0);
		pwm_driver_set(neg, 0);
	}
}