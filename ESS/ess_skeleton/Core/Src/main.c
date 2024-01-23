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

void lab1(void){
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

void brightness(LED_t * led, uint32_t on_time, uint32_t off_time){
	while(1){
		// on for on_time ms
		led_on(led);
		delay_msec(on_time);
		// off for off_time ms
		led_off(led);
		delay_msec(off_time);
	}
}

void brightness_smooth(LED_t * led){
	while(1){
		for(uint32_t on_time = 0; on_time < 10; on_time++){
			// 100ms total
			uint32_t off_time = 10 - on_time;
			for(uint32_t i = 0; i < 10; i++){
				// 10ms total
				// on for on_time ms
				led_on(led);
				delay_msec(on_time);
				// off for off_time ms
				led_off(led);
				delay_msec(off_time);
			}
		}
	}
}

void brightness_switch(LED_t * led1, LED_t * led2){
	while(1){
		for(uint32_t led1_time = 0; led1_time < 10; led1_time++){
			// 100ms total
			uint32_t led2_time = 10 - led1_time;
			for(uint32_t i = 0; i < 10; i++){
				// 10ms total
				// led1 on for led1_time
				led_on(led1);
				led_off(led2);
				delay_msec(led1_time);
				// led2 on for led2_time
				led_off(led1);
				led_on(led2);
				delay_msec(led2_time);
			}
		}
	}
}

void lab2(void){
	/* Initialize system */
	HAL_Init();
	/* Initialize peripherals on board */
	ess_helper_init();

	LED_t led1;
	LED_t led2;
	uint32_t * port = (uint32_t*) 0x40020C14;
	uint32_t led_green_pin=0;
	uint32_t led_red_pin=1;
	led_init(&led1, port, led_green_pin);
	led_init(&led2, port, led_red_pin);

	brightness_switch(&led1, &led2);
}

#include "stm32f4xx.h"
#include "pwm_driver.h"
#define PORTD ((uint32_t*)0x40020C14)

void lab3(void){
	// create led adts
	LED_t led_green;
	LED_t led_orange;
	LED_t led_blue;
	LED_t led_red;

	/* Initialize system */
	HAL_Init();
	/* Initialize peripherals on board */
	ess_helper_init();

	// set up the leds
	led_init(&led_green, PORTD, 0);
	led_init(&led_orange, PORTD, 1);
	led_init(&led_blue, PORTD, 2);
	led_init(&led_red, PORTD, 3);

	// set up pwm driver
	pwm_driver_init(&led_green, &led_red, &led_orange, &led_blue);

	// set brightness values
	pwm_driver_set(0, 0);
	pwm_driver_set(1, 25);
	pwm_driver_set(2, 50);
	pwm_driver_set(3, 100);

	// loop
	while(1){
		delay_msec(1);
		pwm_driver_update();
	}
}

#include "stm32f4xx_hal_tim.h"

TIM_HandleTypeDef TIM_Handle;

void TMR4_Init(void){
	__TIM4_CLK_ENABLE();
	TIM_Handle.Instance = TIM4;
	// timer tick frequency = 8400000 / (0 + 1) = 84000000
	TIM_Handle.Init.Prescaler = 0;
	/* Count up */
	TIM_Handle.Init.CounterMode = TIME_COUNTERMODE_UP;

	/*
	 * Set timer period when it must reset
	 * in our case it is 16 bit = 65535
	 * Frequency = timer_tick_frequency / (TIM_PERIOD + 1)
	 * if period is larger than max timer value need to choose a larger prescaler
	 * and slow down timer tick frequency
	 */
	TIM_Handle.Init.Period = 65535;
	TIM_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM_Handle.Init.RepetitionCounter = 0;
	TIM_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(&TIM_Handle);
	HAL_TIM_Base_Start_IT(&TIM_Handle);
}

void TMR4_WaitForExpiry(void){
	// check the flag, when the timer is expired the flag is SET
	while(__HAL_TIM_GET_FLAG(&TIM_Handle, TIM_FLAG_UPDATE) == RESET){}
	// reset flag for next expirty
	__HAL_TIM_CLEAR_FLAG(&TIM_Handle, TIM_FLAG_UPDATE);
	// reset flag for next expiry
}

void lab4(void){

}

int main(void)
{
	lab3();
}
