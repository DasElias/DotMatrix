/*
 * c1294.c
 *
 * Created: 25.10.2019 13:39:54
 * Author: Elias Horner
 */ 

#include "c1294.h"
#include "usart.h"
#include "max7219.h"

uint8_t characters[][8] = {
	{0x00, 0x7F, 0x88, 0x88, 0x88, 0x88, 0x7F, 0x00},	// A
	{0x00, 0xFF, 0x91, 0x91, 0x91, 0x91, 0x6E, 0x00},	// B
	{0x00, 0x7E, 0x81, 0x81, 0x81, 0x81, 0x42, 0x00},	// C
	{0x00, 0xFF, 0x81, 0x81, 0x81, 0x81, 0x7E, 0x00},	// D
	{0x00, 0xFF, 0x91, 0x91, 0x91, 0x91, 0x81, 0x00},	// E
	{0x00, 0xFF, 0x88, 0x88, 0x88, 0x80, 0x80, 0x00}	// F
};


uint8_t numbers[][8] = {
	{0x00, 0x00, 0x7E, 0x81, 0x81, 0x81, 0x7E, 0x00},	// 0
	{0x00, 0x00, 0x20, 0x40, 0xFF, 0x00, 0x00, 0x00},	// 1
	{0x00, 0x00, 0x43, 0x85, 0x89, 0x71, 0x00, 0x00},
	{0x00, 0x00, 0x42, 0x91, 0x91, 0x91, 0x6E, 0x00},
	{0x00, 0x18, 0x28, 0x48, 0x88, 0xFF, 0x08, 0x00},
	{0x00, 0x00, 0xE2, 0x91, 0x91, 0x91, 0x8E, 0x00},
	{0x00, 0x00, 0x7E, 0x91, 0x91, 0x91, 0x4E, 0x00},
	{0x00, 0x00, 0x80, 0x87, 0x88, 0x90, 0xE0, 0x00},
	{0x00, 0x00, 0x6E, 0x91, 0x91, 0x6E, 0x00, 0x00},
	{0x00, 0x00, 0x72, 0x89, 0x89, 0x89, 0x7E, 0x00}
};

void c1294_transmit(uint8_t address, uint8_t data) {
	spi_select_slave();
	spi_transfer(address);
	spi_transfer(data);
	spi_deselect_slave();
}

void c1294_init(void) {
	spi_init();
	
	// scan limit to 8 LEDs
	c1294_transmit(MAX7219_SCAN_LIMIT, 0x07);

	// deactivate display test
	c1294_transmit(MAX7219_DISPLAY_TEST, MAX7219_DISPLAY_TEST_OFF);
	
	c1294_display_off();
}

void c1294_display_on(void) {
	c1294_transmit(0x0C, 0x1);
}
void c1294_display_off(void) {
	c1294_transmit(0x0C, 0x0);
}

void c1294_display_clear(void) {
	uint8_t empty[C1294_COLS] = {
		0, 0, 0, 0, 0, 0, 0, 0
	};
	c1294_display_1darray_8x8(empty);
}

void c1294_set_intensity(uint8_t intensity) {
	c1294_transmit(MAX7219_INTENSITY, intensity);
}

void c1294_display_1darray_8x8(uint8_t* array) {
	for(uint8_t x = 0; x < C1294_COLS; x++) {
		uint8_t address = C1294_COLS - x;
		
		c1294_transmit(address, array[x]);
	}
}

void c1294_display_2darray_8x8(uint8_t array[C1294_ROWS][C1294_COLS]) {	
	for(uint8_t x = 0; x < C1294_COLS; x++) {
		uint8_t address = C1294_COLS - x;
		
		uint8_t data = 0;
		for(uint8_t y = 0; y < C1294_ROWS; y++) {
			int val = array[y][x];
			
			if(val == 1) {
				data |= (1 << (C1294_ROWS - y - 1));
			}
		}
		c1294_transmit(address, data);
	}
}


/*void c1294_display_running_text(uint8_t textWidth, uint8_t* textArray, uint8_t* p_startIndex, uint8_t* p_width, uint8_t* p_offset) {	
	if((* p_offset) > 0) {
		(* p_offset)--;
		(* p_width)++;
	} else {
		(*p_startIndex)++;
	}
	
	if((* p_startIndex) + 8 >= textWidth) {
		(*p_width)--;
	}
	if((* p_startIndex) == textWidth) {
		(* p_startIndex) = 0;
		(* p_width) = 0;
		(* p_offset) = 8;
	}
	
	uint8_t temp[C1294_ROWS][C1294_COLS];
	for(int x = 0; x < C1294_COLS; x++) {
		for(int y = 0; y < C1294_ROWS; y++) {
			if(x > (* p_width) + (* p_offset) || x < (* p_offset)) temp[y][x] = 0;
			else {
				uint8_t textArray_x = (* p_startIndex) + x - (* p_offset);
				temp[y][x] = textArray[(C1294_ROWS) * textArray_x + y];
			}
		}
	}
	
	c1294_display_2darray_8x8(temp);
}*/

void c1294_display_running_text(uint8_t textWidth, uint8_t* textArray, uint8_t* p_startIndex, uint8_t* p_width, uint8_t* p_offset) {
	if((* p_offset) > 0) {
		(* p_offset)--;
		(* p_width)++;
	} else {
		(*p_startIndex)++;
	}
	
	if((* p_startIndex) + 8 >= textWidth) {
		(*p_width)--;
	}
	if((* p_startIndex) == textWidth) {
		(* p_startIndex) = 0;
		(* p_width) = 0;
		(* p_offset) = 8;
	}
	
	uint8_t temp[C1294_COLS];
	for(int x = 0; x < C1294_COLS; x++) {
		if(x > (* p_width) + (* p_offset) || x < (* p_offset)) temp[x] = 0;
		else {
			uint8_t textArray_x = (* p_startIndex) + x - (* p_offset);
			temp[x] = textArray[textArray_x];
		}
	}
	
	c1294_display_1darray_8x8(temp);
}


void c1294_display_number(uint8_t n) {
	if(n <= 9) {
		c1294_display_1darray_8x8(numbers[n]);
	}
}

void c1294_display_character(char character) {
	if(character >= 0x41 && character <= 0x46) {
		c1294_display_1darray_8x8(characters[character - 0x41]);
	}
}