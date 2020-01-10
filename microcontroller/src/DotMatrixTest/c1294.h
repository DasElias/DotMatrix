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

#include <stdint.h>

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

void c1294_display_1darray_8x8(uint8_t array[C1294_COLS]);


/// <summary>Display a running text, which runs from the right to the left side of the LED matrix.</summary>
/// <remarks>
/// Dims the display. The luminance is determined by the formula
/// 2*intensity+1/32. Intensity ranges from 0 to 15. Please refer
/// to page 9 of the data sheet for the details.
/// </remarks>
/// <param name="textArray">An array, which contains the whole text to display. The array is accessed with [C1294_ROWS * x + y]</param>
/// <param name="startIndex">The index in textArray of the first column to display. Before this function is called the first time, this value must be set to 0. Afterwards, it must not change any more.</param>
/// <param name="width">Before this function is called the first time, this value must be set to 0. Afterwards, it must not change any more.</param>
/// <param name="offset">Before this function is called the first time, this value must be set to 8. Afterwards, it must not change any more.</param>
void c1294_display_running_text(uint8_t textWidth, uint8_t* textArray, uint8_t* startIndex, uint8_t* width, uint8_t* offset);

/// <summary>Display a number.</summary>
/// <remarks>
/// Displays a number by transmitting the corresponding pattern
/// to the controller. Just one digit can be displayed.
/// </remarks>
/// <param name="number">The number to be displayed.</param>
void c1294_display_number(uint8_t number);

/// <summary>Display a character.</summary>
/// <remarks>
/// Displays a character by transmitting the corresponding pattern
/// to the controller. All printable ASCII signs can be specified.
/// </remarks>
/// <param name="character">The character to be displayed.</param>
void c1294_display_character(char character);

	


#endif /* C1294_H_ */