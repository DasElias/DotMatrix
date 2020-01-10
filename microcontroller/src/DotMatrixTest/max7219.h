/** \file max7219.h
 *
 * \brief  Header file for the MAX7219 serially interfaced, 8-Digit LED display driver.
 *
 * This file defines the pin mapping and the register addresses for the
 * Maxim MAX7219 display driver.
 *
 * \author    Wolfgang Neff
 * \version   1.0
 * \date      2018-03-08
 *
 * \par History
 *      Created: 2018-03-08
 */

#ifndef MAX7219_H_
#define MAX7219_H_

#include "spi.h"

/**** Pin description *****/

#define MAX7219_PORT SPI_PORT
#define MAX7219_MODULE SPI_MODULE

/* Serial-Data Input */
#define MAX7219_DIN_bp SPI_MOSI_bp
#define MAX7219_DIN_bm SPI_MOSI_bm

/* Serial-Data Output */
#define MAX7219_DOUT_bp SPI_MISO_bp
#define MAX7219_DOUT_bm SPI_MISO_bm

/* Serial-Clock Input */
#define MAX7219_CLK_bp SPI_SCK_bp
#define MAX7219_CLK_bm SPI_SCK_bm

/* Chip-Select Input */
#define MAX7219_CS_bp SPI_SS_bp
#define MAX7219_CS_bm SPI_SS_bm


/**** Register address *****/

#define MAX7219_NO_OP 0x00
#define MAX7219_DECODE_MODE 0x09
#define MAX7219_INTENSITY 0x0A
#define MAX7219_SCAN_LIMIT 0x0B

/* Shutdown Register Address and Format */
#define MAX7219_SHUTDOWN 0x0C
#define MAX7219_SHUTDOWN_ON 0x00
#define MAX7219_SHUTDOWN_OFF 0x01

/* Display-Test Register Address and Format */
#define MAX7219_DISPLAY_TEST 0x0F
#define MAX7219_DISPLAY_TEST_ON 0x01
#define MAX7219_DISPLAY_TEST_OFF 0x0

#endif /* MAX7219_H_ */