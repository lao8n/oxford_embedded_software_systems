/* Includes ------------------------------------------------------------------*/
#include "ess_helper.h"
#include "led_driver.h"
#include "stdio.h"
#include "delay.h"
#include "stm32f4xx.h"
#include "pwm_driver.h"
#include "stm32f4xx_hal_tim.h"

#define PORTD ((uint32_t*)0x40020C14)

int _write(int file, char *ptr, int len){
	int i = 0;
	for(i = 0; i < len; i++){
		ITM_SendChar((*ptr++));
	}
	return len;
}

TIM_HandleTypeDef TIM_Handle;

void TMR4_Init(void){
	__TIM4_CLK_ENABLE();
	TIM_Handle.Instance = TIM4;
	// timer tick frequency = 8400000 / (0 + 1) = 84000000
	TIM_Handle.Init.Prescaler = 0;
	/* Count up */
	TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;

	/*
	 * Set timer period when it must reset
	 * in our case it is 16 bit = 65535
	 * Frequency = timer_tick_frequency / (TIM_PERIOD + 1)
	 * if period is larger than max timer value need to choose a larger prescaler
	 * and slow down timer tick frequency
	 */
	TIM_Handle.Init.Period = 8399; // 32 Hz
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

int main(void){
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

	// timer init
	TMR4_Init();

	// loop
	while(1){
		TMR4_WaitForExpiry();
		pwm_driver_update();
	}
}
