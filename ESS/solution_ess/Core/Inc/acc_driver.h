/*
 * acc_driver.h
 *
 *  Created on: 30 Jan 2022
 *      Author: zhuangzhuangdai
 */

#ifndef INC_ACC_DRIVER_H_
#define INC_ACC_DRIVER_H_

#include "spi_driver.h"

typedef struct{
	int16_t x;
	int16_t y;
	int16_t z;
}acc3_t;

uint8_t AccInit(void);
void AccRead(acc3_t * reading);

#endif /* INC_ACC_DRIVER_H_ */
