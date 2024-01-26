#include "stm32f4xx_hal.h"
#include "display_driver.h"

TIM_HandleTypeDef TIM_Handle3;
TIM_HandleTypeDef TIM_Handle4;

// Hardware timer is more accurate but still uses 100% of CPU when it checks the flag. If is doing something else then it could miss the flag and lead to jitter.
// Better to use ISR instea
void TMR4_Init_ISR(void){
	__TIM4_CLK_ENABLE();
	TIM_Handle4.Instance = TIM4;
	// timer tick frequency = 8400000 / (0 + 1) = 84000000
	TIM_Handle4.Init.Prescaler = 0;
	/* Count up */
	TIM_Handle4.Init.CounterMode = TIM_COUNTERMODE_UP;

	/*
	 * Set timer period when it must reset
	 * in our case it is 16 bit = 65535
	 * Frequency = timer_tick_frequency / (TIM_PERIOD + 1)
	 * if period is larger than max timer value need to choose a larger prescaler
	 * and slow down timer tick frequency
	 */
	TIM_Handle4.Init.Period = 8399; // 32Hz
	TIM_Handle4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM_Handle4.Init.RepetitionCounter = 0;
	TIM_Handle4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(&TIM_Handle4);
	HAL_TIM_Base_Start_IT(&TIM_Handle4);
	// Enable TIM4 global interrupt
	HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0); // changed to 0
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
}

void TIM4_IRQHandler(void){
	// check the flag, in case other interrupts are also
	if(__HAL_TIM_GET_FLAG(&TIM_Handle4, TIM_FLAG_UPDATE) != RESET){
		if(__HAL_TIM_GET_ITSTATUS(&TIM_Handle4, TIM_IT_UPDATE) != RESET){
			__HAL_TIM_CLEAR_FLAG(&TIM_Handle4, TIM_FLAG_UPDATE);
			pwm_driver_update();
		}
	}
}

// Hardware timer is more accurate but still uses 100% of CPU when it checks the flag. If is doing something else then it could miss the flag and lead to jitter.
// Better to use ISR instea
void TMR3_Init_ISR(void){
	__TIM3_CLK_ENABLE();
	TIM_Handle3.Instance = TIM3;
	// timer tick frequency = 8400000 / (0 + 1) = 84000000
	TIM_Handle3.Init.Prescaler = 0;
	/* Count up */
	TIM_Handle3.Init.CounterMode = TIM_COUNTERMODE_UP;

	/*
	 * Set timer period when it must reset
	 * in our case it is 16 bit = 65535
	 * Frequency = timer_tick_frequency / (TIM_PERIOD + 1)
	 * if period is larger than max timer value need to choose a larger prescaler
	 * and slow down timer tick frequency
	 */
	TIM_Handle3.Init.Period = 8399; // 32Hz
	TIM_Handle3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM_Handle3.Init.RepetitionCounter = 0;
	TIM_Handle3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(&TIM_Handle3);
	HAL_TIM_Base_Start_IT(&TIM_Handle3);
	// Enable TIM4 global interrupt
	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0); // changed to 0
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM3_IRQHandler(void){
	// check the flag, in case other interrupts are also
	if(__HAL_TIM_GET_FLAG(&TIM_Handle3, TIM_FLAG_UPDATE) != RESET){
		if(__HAL_TIM_GET_ITSTATUS(&TIM_Handle3, TIM_IT_UPDATE) != RESET){
			__HAL_TIM_CLEAR_FLAG(&TIM_Handle3, TIM_FLAG_UPDATE);
		}
	}
}
