#include "main.h"

struct LEDstruct {
	uint32_t * port; // led register
	uint32_t pin; // 0..15
};
typedef struct LEDstruct LED_t;

void led_init(LED_t *led, uint32_t * port, uint32_t pin);
void led_on(LED_t * led);
void led_off(LED_t * led);
void delay_msec(uint32_t delay);