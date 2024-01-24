/*
 * pwm_driver.h
 *
 *  Created on: 26 Jan 2022
 *      Author: zhuangzhuangdai
 */

#ifndef INC_PWM_DRIVER_H_
#define INC_PWM_DRIVER_H_

#include <stdint.h>
#include "led_driver.h"

typedef enum{
	CLOCKWISE = 0x01,
	COUNTER_CLOCKWISE,
}flash_states_t;

void pwm_driver_init(LED_t * ch0, LED_t *ch1, LED_t * ch2, LED_t * ch3);
void pwm_driver_set(uint8_t channel, uint8_t value);
void pwm_driver_update(void);

#endif /* INC_PWM_DRIVER_H_ */
