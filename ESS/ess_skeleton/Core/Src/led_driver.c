#include "led_driver.h"

void led_init(LED_t *led, uint32_t * port, uint32_t pin){
	led->port = port;
	led->pin = pin;
	(*led->port) &= 0x1000;
}

void led_on(LED_t * led){
	(*led->port) |= 0x1000 << led->pin;
}

void led_off(LED_t * led){
	(*led->port) &=~ (0x1000 << led->pin);
}

void delay_msec(uint32_t delay){
	int i = 0;
	while(i < 20000 * delay){
		i++;
	}
}

void button_init(Button_t * b, uint32_t port){
	(b->port) = (uint32_t*) port;
}

void button_loop(Button_t * b, LED_t * led){
	while(1){
		if((*b->port)){
			led_on(led);
		} else {
			led_off(led);
		}
	}
}
