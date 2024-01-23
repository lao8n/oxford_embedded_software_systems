/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ess_helper.h"

struct LEDstruct {
	uint32_t * port; // led register
	uint32_t pin; // 0..15
};
typedef struct LEDstruct LED_t;

void led_init(LED_t * led, uint32_t * port, uint32_t pin);
void led_on(LED_t * led);
void led_off(LED_t * led);

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
	led_init(&led, port, led_blue_pin);
	led_on(&led);
    while(1){
    }
}

