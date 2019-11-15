/** \file usart.h
*
* \brief This module enables communication via USART.
*
* \author    Wolfgang Neff
* \version   2.0
* \date      2018-07-04
*
* \par History
*      Created: 2012-09-03 \n
*      Modified: 2014-10-17 \n
*      Modified: 2015-01-28 \n
*      Modified: 2018-07-04
*/

#ifndef USART_H_
#define USART_H_

#include "board.h"

#define USART_PORT USB_USART_PORT
#define USART_MODULE USB_USART_MODULE

#define USART_RX_PIN_bp USB_USART_RX_PIN_bp
#define USART_RX_PIN_bm USB_USART_RX_PIN_bm

#define USART_TX_PIN_bp USB_USART_TX_PIN_bp
#define USART_TX_PIN_bm USB_USART_TX_PIN_bm

#define USART_DRE_vect USB_USART_DRE_vect
#define USART_RXC_vect USB_USART_RXC_vect

#define USART_BSEL_gc 11
#define USART_BSCALE_gc -7
#define USART_CONFIG (USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc)


#ifdef __cplusplus
extern "C"
{
#endif

/// <summary>Initialize the USART.</summary>
/// <remarks>
/// Initializes the USART the gateway. The baud rate and the serial
/// line parameters can be specified by the predefined constants.
/// </remarks>
void usart_init(void);

/// <summary>Receive complete.</summary>
/// <remarks>
/// Checks if a new data byte has been received.
/// </remarks>
/// <returns>True if a data byte has been received.</returns>
uint8_t usart_receive_complete(void);

/// <summary>Receive data.</summary>
/// <remarks>
/// Waits until a byte of data has been received and returns it.
/// </remarks>
/// <returns>The data received.</returns>
uint8_t usart_receive(void);


#ifdef __cplusplus
}
#endif

#endif /* USART_H_ */