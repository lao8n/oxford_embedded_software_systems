#include "main.h"

#include "stm32f4xx_hal_tim.h"

void TMR4_Init(void);
void TMR4_WaitForExpiry(void);
void delay_msec_hrdw(uint32_t delay);
void delay_msec_hrdw(uint32_t delay){
	TMR4_WaitForExpiry();
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