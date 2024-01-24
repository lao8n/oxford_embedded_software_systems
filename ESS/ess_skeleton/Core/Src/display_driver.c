#include "display_driver.h"
#include "led_driver.h"
#include "pwm_driver.h"

#define PORTD ((uint32_t*)0x40020C14)


void display_init(void){
	// create led adts
	LED_t led_green;
	LED_t led_orange;
	LED_t led_blue;
	LED_t led_red;

	// set up the leds
	led_init(&led_green, PORTD, 0);
	led_init(&led_orange, PORTD, 1);
	led_init(&led_blue, PORTD, 2);
	led_init(&led_red, PORTD, 3);

	// set up pwm driver
	pwm_driver_init(&led_green, &led_red, &led_orange, &led_blue);
}

void display_tilt(int8_t x_tilt, int8_t y_tilt){
	assert(x_tilt >= -90);
	assert(x_tilt <= 90);
	assert(y_tilt >= -90);
	assert(y_tilt <= 90);

	if(x_tilt >= 0){
		pwm_driver_set(GREEN, 0);
		// brightness
		pwm_driver_set(RED, 100);
	} else {
		pwm_driver_set(RED, 0);
		pwm_driver_set(GREEN, 100);
	}
	if(y_tilt >= 0){
		pwm_driver_set(BLUE, 0);
		pwm_driver_set(ORANGE, 100);
	} else {
		pwm_driver_set(ORANGE, 0);
		pwm_driver_set(BLUE, 100);
	}
}
