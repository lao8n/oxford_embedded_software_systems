/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ess_helper.h"

// Initialize the green LED.
void led_green_init(uint32_t pin);
// Turn the green LED on
void led_green_on(void);
// Turn the green LED off
void led_green_off(void);
// Initialize the green LED.
void led_red_init(void);
// Turn the green LED on
void led_red_on(void);
// Turn the green LED off
void led_red_off(void);

int main(void)
{
	/* Initialize system */
	HAL_Init();
	/* Initialize peripherals on board */
	ess_helper_init();
	*(uint32_t*)0x40020C14 = 0xF000;

	// led pins
	static uint32_t led_green_pin=1;

	// Set all the LEDs to on.
	led_green_init(led_green_pin);
	led_green_on();
    while(1){
    }
}

void led_green_init(uint32_t pin) {
	*(uint32_t*)0x40020C14 &= pin;
}
void led_green_on(void) {
	*(uint32_t*)0x40020C14 |= 0x1000 << 0;
}
void led_green_off() {
	*(uint32_t*)0x40020C14 &=~ 0x1000 << 0;
}

void led_red_init(){
	*(uint32_t*)0x40020C14 &= 0x2000;
}

void led_red_on() {
	*(uint32_t*)0x40020C14 |= 0x2000;
}
void led_red_off() {
	*(uint32_t*)0x40020C14 &=~ 0x2000;
}

void led_orange_init(){
	*(uint32_t*)0x40020C14 &= 0x4000;
}

void led_orange_on() {
	*(uint32_t*)0x40020C14 |= 0x4000;
}
void led_orange_off() {
	*(uint32_t*)0x40020C14 &=~ 0x4000;
}

void led_blue_init(){
	*(uint32_t*)0x40020C14 &= 0x8000;
}

void led_blue_on() {
	*(uint32_t*)0x40020C14 |= 0x8000;
}
void led_blue_off() {
	*(uint32_t*)0x40020C14 &=~ 0x8000;
}

