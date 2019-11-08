/*
 * \file spi.c
 *
 * \date 18.10.2019 10:56:52
 * \author Elias Horner
 */ 

#include "spi.h"

void spi_init(void) {
	// deactivate slave by setting the SS-bit
	SPI_PORT.OUT |= SPI_SS_bm;
	
	// make MISO an input line
	SPI_PORT.DIR &= ~SPI_MISO_bm;
	
	// make SS, MOSI and SCK output lines
	SPI_PORT.DIR |= SPI_SS_bm | SPI_MOSI_bm | SPI_SCK_bm;
	
	// enable SPI, select master mode and set the prescaler factor to 64
	SPI_MODULE.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_PRESCALER_DIV64_gc;
}

void spi_select_slave(void) {
	// select slave by clearing the SS-bit
	SPI_PORT.OUT &= ~SPI_SS_bm;
}

void spi_deselect_slave(void) {
	// deactivate slave by setting the SS-bit
	SPI_PORT.OUT |= SPI_SS_bm;
}

uint8_t spi_transfer(uint8_t byte) {
	// send data
	SPI_MODULE.DATA = byte;
	
	// wait until transmission has finished (until the IF-bit is set)
	while (!(SPI_MODULE.STATUS & SPI_IF_bm)) {
		// do nothing
	}
	
	return SPI_MODULE.DATA;
}
