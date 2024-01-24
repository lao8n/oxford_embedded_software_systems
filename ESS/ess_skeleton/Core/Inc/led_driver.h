#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>

struct LEDstruct {
	uint32_t * port; // led register
	uint32_t pin; // 0..15
};
typedef struct LEDstruct LED_t;

void led_init(LED_t *led, uint32_t * port, uint32_t pin);
void led_on(LED_t * led);
void led_off(LED_t * led);

struct Buttonstruct {
	uint32_t * port; // input button register
};
typedef struct Buttonstruct Button_t;
void button_init(Button_t * b, uint32_t port);
void button_loop(Button_t * b, LED_t * led);

#endif
