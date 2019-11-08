/*
 * c1294.c
 *
 * Created: 25.10.2019 13:39:54
 *  Author: Elias
 */ 

#include "c1294.h"

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
	uint8_t empty[C1294_COLS * C1294_ROWS] = {
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


