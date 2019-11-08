#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

#define SPI_PORT PORTF
#define SPI_MODULE SPIF

#define SPI_SS_bp    PIN4_bp
#define SPI_MOSI_bp  PIN5_bp
#define SPI_MISO_bp  PIN6_bp
#define SPI_SCK_bp   PIN7_bp

#define SPI_SS_bm    PIN4_bm
#define SPI_MOSI_bm  PIN5_bm
#define SPI_MISO_bm  PIN6_bm
#define SPI_SCK_bm   PIN7_bm

#define SPI_CLOCK_SPEED_gc SPI_PRESCALER_DIV4_gc

#ifdef __cplusplus
extern "C"
{
	#endif
	
	void spi_init(void);
	
	void spi_select_slave(void);
	
	void spi_deselect_slave(void);
	
	uint8_t spi_transfer(uint8_t byte);
	
	#ifdef __cplusplus
}
#endif

#endif /* SPI_H_ */