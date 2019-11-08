/*
 * DotMatrix.c
 *
 * Created: 18.10.2019 10:50:05
 * Author : Elias
 */ 

#include <avr/io.h>
#include "c1294.h"


int main(void) {
 uint8_t arr[8][8] = {
		{1,0,0,0,0,0,0,0},
		{0,1,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0},
		{0,0,0,1,0,0,0,0},
		{0,0,0,0,1,0,0,0},
		{0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,1},
	};

	c1294_init();
	c1294_display_on();
	c1294_set_intensity(15);
	
	while(1) {		
		c1294_display_2darray_8x8(arr);
		
	//	_delay_ms(1000);
	}
   
}

