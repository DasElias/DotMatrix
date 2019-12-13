/*
 * usart.c
 *
 * Created: 15.11.2019 10:45:08
 *  Author: Fabio Curman
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "c1294.h"

void usart_init(void){
	/***** Configure the USART pins *****/
	// The RX pin is input. We ensure this by clearing DIR although this is default.
	USB_USART_PORT.DIR &= ~USB_USART_RX_PIN_bm;
	
	/***** Configure the USART module *****/
	// We are using the USB-to-USART gateway. Its configuration is 115200 8N1.
	// Baud rate is 115200 bps. See baud rate table.
	USB_USART_MODULE.BAUDCTRLA = 11;
	USB_USART_MODULE.BAUDCTRLB = (-7<<USART_BSCALE_gp);
	// Line configuration is 8 data bits, no parity, 1 stop bit.
	USB_USART_MODULE.CTRLC = (USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc);
	// Enable receiver.
	USB_USART_MODULE.CTRLB = USART_RXEN_bm;
	
	// enable low-level interrupts.
	PMIC.CTRL |= PMIC_LOLVLEN_bm;
	CPU_SREG |= CPU_I_bm;
	USB_USART_MODULE.CTRLA |= USART_RXCINTLVL_LO_gc;
}
