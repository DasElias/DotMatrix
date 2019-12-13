/*
 * c1294.c
 *
 * Created: 25.10.2019 13:39:54
 *  Author: Elias
 */ 

#include "c1294.h"
#include "usart.h"

uint8_t data[][8] = {
	{0x00, 0xF8, 0x88, 0x88, 0x88, 0x88, 0xFB, 0x00},
	{0x00, 0xFF, 0x19, 0x19, 0x19, 0x19, 0xE6, 0x00},
	{
		0x00, 0xE7, 0x18, 0x18, 0x18, 0x18, 0x24, 0x00
	},
	{
		0x00, 0xFF, 0x18, 0x18, 0x18, 0x18, 0xEB, 0x00
	},
	{
		0x00, 0xFF, 0x19, 0x19, 0x19, 0x19, 0x18, 0x00
	},
	{	
		0x00, 0xFF, 0x88, 0x88, 0x88, 0x08, 0x08, 0x00
	}
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
	c1294_transmit(0x0B, 0x07);

	// deactivate display test
	c1294_transmit(0x0F, 0x0);
	
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
	c1294_transmit(0x0A, intensity);
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


void c1294_display_number(uint8_t number) {

}

void c1294_display_character(char character) {
	if(character >= 0x41 && character <= 0x46) {
		c1294_display_1darray_8x8(data[character - 0x41]);
	}
}