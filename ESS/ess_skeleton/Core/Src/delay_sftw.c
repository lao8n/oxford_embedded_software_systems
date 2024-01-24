#include "delay.h"

void delay_msec(uint32_t delay){
	int i = 0;
	while(i < 20000 * delay){
		i++;
	}
}

void delay_usec(uint32_t delay){
	int i = 0;
	while(i < 20 * delay){
		i++;
	}
}