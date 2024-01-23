/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ess_helper.h"

int main(void)
{
	/* Initialize system */
	HAL_Init();
	/* Initialize peripherals on board */
	ess_helper_init();
	// Set all the LEDs to on.


	// Initialize the green LED.
	void led_green_init(void);
	// Turn the green LED on
	void led_green_on(void);
	// Turn the green LED off
	void led_green_off(void);


	*(uint32_t*)0x40020C14 = 0xF000;

	void led_green_init() {
		*(uint32_t*)0x40020C14 & 0x1000;
	}
	void led_green_on() {
		*(uint32_t*)0x40020C14 | 0x1000;
	}
	void led_green_off() {
		*(uint32_t*)0x40020C14 & 0x1000;
	}

	led_green_init();
	led_green_on();

    while(1){
    }
}
