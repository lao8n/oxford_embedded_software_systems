/*
 * led_driver.h
 *
 *  Created on: 23 Jan 2022
 *      Author: zhuangzhuangdai
 */

#ifndef INC_LED_DRIVER_H_
#define INC_LED_DRIVER_H_

#define PORTD ((volatile uint32_t*)0x40020C14)
#define GREEN 12
#define ORANGE 13
#define RED 14
#define BLUE 15

typedef struct{
	volatile uint32_t * port; //pointer of led register
	uint32_t pin; //12 ~ 15
}LED_t;

typedef enum{
	ONLY_GREEN = 0x01,
	ONLY_ORANGE,
	ONLY_RED,
	ONLY_BLUE
}led_states_t;

void led_init(LED_t* led, volatile uint32_t* port, uint32_t pin);
void led_off(LED_t* led);
void led_on(LED_t* led);

#endif /* INC_LED_DRIVER_H_ */
