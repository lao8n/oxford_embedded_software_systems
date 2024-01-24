#include "stdint.h"

typedef enum {
	GREEN = 0,
	ORANGE,
	BLUE,
	RED} colour;

void display_init(void);
void display_tilt(int8_t x_tilt, int8_t y_tilt);
