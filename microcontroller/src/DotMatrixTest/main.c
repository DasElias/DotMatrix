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

#define CAPACITY 8


// Variables which are changed by interrupts must be declared as volatile.
volatile uint8_t buf1[8];
volatile uint8_t buf2[8];

volatile uint8_t* readBuffer = buf1;
volatile uint8_t* writeBuffer = buf2;


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
			/*numberToDisplay++;
			if(numberToDisplay > 9) numberToDisplay = 0;*/
			_delay_ms(500);
		} else if (activeState == DISPLAY_CHARACTERS) {
			//charToDisplay++;
			if(charToDisplay > 0x46) {
				charToDisplay = 0x41;	// A
			}
			c1294_display_character(charToDisplay);
			_delay_ms(500);
		} else if (activeState == DISPLAY_USART_PATTERN) {
			uint8_t temp[8] = {readBuffer[0], readBuffer[1], readBuffer[2], readBuffer[3], readBuffer[4], readBuffer[5], readBuffer[6], readBuffer[7]};
			c1294_display_1darray_8x8(temp);
			_delay_ms(500);
		}
		
		
		//uint8_t temp[8] = {readBuffer[0], readBuffer[1], readBuffer[2], readBuffer[3], readBuffer[4], readBuffer[5], readBuffer[6], readBuffer[7]};
		//c1294_display_1darray_8x8(temp);
	/*	c1294_read_from_usart(usartValues);
		c1294_display_1darray_8x8(usartValues);*/
	
		
		//_delay_ms(1000);
	}
   
}

volatile uint8_t ctr = 0;
ISR(USB_USART_RXC_vect){
	writeBuffer[ctr] = USB_USART_MODULE.DATA;
	ctr++;
	if(ctr >= CAPACITY) {
		ctr = 0;
		volatile uint8_t* temp = writeBuffer;
		writeBuffer = readBuffer;
		readBuffer = temp;
	}
}

