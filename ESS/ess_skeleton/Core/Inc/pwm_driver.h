/**
 * Four Channel PWM driver
 */

#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H

#include <stdint.h>
#include "led_driver.h"

#define PWM_MAX 100

/*
 * initialize pwm driver
 * @warning assumes that led_init() has been called for each led
 */
void pwm_driver_init(LED_t *ch0, LED_t *ch1, LED_t *ch2, LED_t *ch3);

/*
 * set brightness for particular channel, values range between 0-100 for 0-100%
 */
void pwm_driver_set(uint8_t channel, uint8_t value);

/*
 * update pwm output for each channel - it is called periodically and decides whether to turn on
 * or off
 * @warning assumes that pwm_driver_init() has been called
 */
void pwm_driver_update(void);

/*
 * update pwm output for each channel slowly
 * @warning assumes that pwm_driver_init() has been called
 */
void pwm_driver_fade_update(void);

#endif