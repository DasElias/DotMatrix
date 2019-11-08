/** \file c1294.h
 *
 * \brief This module implements an interface to the MIKROE-1294 8x8 Y Click.
 *
 * The MIKROE-1294 8x8 Y Click implements a 8x8 dot-matrix using a MAX7219
 * serially interfaced 8-Digit LED display driver. This module provides an
 * interface to this module.
 *
 * \author    Wolfgang Neff
 * \version   1.0
 * \date      2018-03-08
 *
 * \par History
 *      Created: 2018-03-08
 */

#ifndef C1294_H_
#define C1294_H_
#include "spi.h"

#define C1294_COLS 8
#define C1294_ROWS 8

/**** Low level functions *****/

/// <summary>Transmit data.</summary>
/// <remarks>
/// Transmits data to the specified register.
/// </remarks>
/// <param name="address">The addressed register.</param>
/// <param name="data">The data to be transmitted.</param>
void c1294_transmit(uint8_t address, uint8_t data);

/**** High level functions *****/

/// <summary>Initialize click module.</summary>
/// <remarks>
/// Initializes the click module by setting up the SPI
/// module and configuring the module. Decode mode is
/// turned off and the scan limit comprises all digits.
/// The display is turned off after initialization.
/// </remarks>
void c1294_init(void);

/// <summary>Turn display on.</summary>
/// <remarks>
/// Turns the display on by leaving shutdown mode.
/// </remarks>
void c1294_display_on(void);

/// <summary>Turn display off.</summary>
/// <remarks>
/// Turns the display on by entering shutdown mode.
/// </remarks>
void c1294_display_off(void);

/// <summary>Clear display.</summary>
/// <remarks>
/// Clears the display by turning all LEDs off.
/// </remarks>
void c1294_display_clear(void);

/// <summary>Dim display.</summary>
/// <remarks>
/// Dims the display. The luminance is determined by the formula
/// 2*intensity+1/32. Intensity ranges from 0 to 15. Please refer
/// to page 9 of the data sheet for the details.
/// </remarks>
/// <param name="intensity">The intensity of the luminance.</param>
void c1294_set_intensity(uint8_t intensity);

void c1294_display_1darray_8x8(uint8_t* array);

void c1294_display_2darray_8x8(uint8_t array[C1294_ROWS][C1294_COLS]);


#endif /* C1294_H_ */