/*
 * DotMatrix.c
 *
 * Created: 18.10.2019 10:50:05
 * Author: Elias Horner
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "c1294.h"
#include "usart.h"
#include "interrupt.h"


int main(void) {		
	uint8_t runningTextData[] = {
		0x00, 0xFF, 0x08, 0x08, 0x08, 0x08, 0xFF,	// H
		0x00, 0x3F, 0x48, 0x88, 0x88, 0x48, 0x3F,	// A
		0x00, 0xFF, 0x01, 0x01, 0x01,				// L
		0x00, 0xFF, 0x01, 0x01, 0x01,				// L
		0x00, 0x7E, 0x81, 0x81, 0x81, 0x81, 0x7E,	// O
		0x00, 0x00, 0x00, 0x00,								// space
		0xFE, 0x01, 0x02, 0x04, 0x02, 0x01, 0xFE,	// W
		0x00, 0xFF, 0x89, 0x89, 0x89, 0x81, 0x81,	// E
		0x00, 0xFF, 0x01, 0x01, 0x01,				// L
		0x00, 0x80, 0x80, 0xFF, 0x80, 0x80,			// T
	};
	int runningTextSize = sizeof(runningTextData) / sizeof(runningTextData[0]);

	c1294_init();
	c1294_display_on();
	c1294_set_intensity(15);
	c1294_display_clear();
	
	usart_init();
	interrupt_init();
	
	// RUNNING TEXT
	uint8_t startIndex = 0;
	uint8_t width = 0;
	uint8_t offset = 8;
	
	// NUMBERS
	uint8_t numberToDisplay = 0;

	// CHARACTERS
	char charToDisplay = 0x41; // A
	
	while(1) {		
		int8_t activeState = getActiveStatus();
		
		if(activeState == DISPLAY_RUNNING_TEXT) {
			c1294_display_running_text(runningTextSize, runningTextData, &startIndex, &width, &offset);
			_delay_ms(500);
		} else if (activeState == DISPLAY_NUMBERS) {
			numberToDisplay++;
			if(numberToDisplay > 9) numberToDisplay = 0;
			c1294_display_number(numberToDisplay);
			
			_delay_ms(1000);
		} else if (activeState == DISPLAY_CHARACTERS) {
			c1294_display_character(charToDisplay);
			charToDisplay++;
			if(charToDisplay > 0x46) {
				charToDisplay = 0x41;	// set character back to A
			}
			
			_delay_ms(1000);
		} else if (activeState == DISPLAY_USART_PATTERN) {
			uint8_t temp[8];
			usart_get_data(temp);
			c1294_display_1darray_8x8(temp);
			
			_delay_ms(500);
		}
	}
}


