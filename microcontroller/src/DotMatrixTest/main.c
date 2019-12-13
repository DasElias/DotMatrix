/*
 * DotMatrix.c
 *
 * Created: 18.10.2019 10:50:05
 * Author : Elias
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "c1294.h"
#include "usart.h"
#include "interrupt.h"
#define ARRAY_WIDTH 19


int main(void) {	
	/*uint8_t arr[8][19] = {
		{1,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
		{1,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
		{1,1,1,1,0,0,1,1,0,0,1,0,1,0,0,1,1,1,0},
		{1,0,0,1,0,1,0,0,1,0,1,0,1,0,1,0,0,0,1},
		{1,0,0,1,0,1,1,1,0,0,1,0,1,0,1,0,0,0,1},
		{1,0,0,1,0,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
		{1,0,0,1,0,0,1,1,0,0,1,0,1,0,0,1,1,1,0},
		{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0}
	};
	
	uint8_t oneDimensionalArray[8 * ARRAY_WIDTH];
	for(int y = 0; y < 8; y++) {
		for(int x = 0; x < ARRAY_WIDTH; x++) {
			oneDimensionalArray[(C1294_ROWS) * x + y] = arr[y][x];
		}
	}*/
	
	uint8_t oneDimensionalArray[ARRAY_WIDTH] = {
		0x00, 0x7F, 0x88, 0x88, 0x88, 0x88, 0x88, 0x7F,
		0x00, 0xFF, 0x91, 0x91, 0x91, 0x91, 0x6E, 0x00
	};

	c1294_init();
	c1294_display_on();
	c1294_set_intensity(15);
	c1294_display_clear();
	
	usart_init();
	interrupt_init();
	
	// DISPLAY_RUNNING_TEXT
	uint8_t startIndex = 0;
	uint8_t width = 0;
	uint8_t offset = 8;
	
	// ACTIVE NUMBER
	uint8_t numberToDisplay = 0;

	// ACTIVE CHAR
	char charToDisplay = 0x41; // A
	
	while(1) {		
		int8_t activeState = getActiveStatus();
		
		if(activeState == DISPLAY_RUNNING_TEXT) {
			c1294_display_running_text(ARRAY_WIDTH, oneDimensionalArray, &startIndex, &width, &offset);
			_delay_ms(500);
		} else if (activeState == DISPLAY_NUMBERS) {
			numberToDisplay++;
			if(numberToDisplay > 9) numberToDisplay = 0;
			c1294_display_number(numberToDisplay);
			
			_delay_ms(3000);
		} else if (activeState == DISPLAY_CHARACTERS) {
			//charToDisplay++;
			if(charToDisplay > 0x46) {
				charToDisplay = 0x41;	// A
			}
			c1294_display_character(charToDisplay);
			
			_delay_ms(500);
		} else if (activeState == DISPLAY_USART_PATTERN) {
			uint8_t temp[8];
			usart_get_data(temp);
			c1294_display_1darray_8x8(temp);
			
			_delay_ms(500);
		}
	}
}


