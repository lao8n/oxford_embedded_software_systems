#ifndef __DISPLAY_DRIVER_H
#define __DISPLAY_DRIVER_H

#include "stdint.h"

typedef enum {
	GREEN = 0,
	ORANGE,
	BLUE,
	RED} colour_t;

void display_init(void);
void display_axis(int16_t axis, colour_t neg, colour_t pos);

#endif
