/*
 * usart.c
 *
 * Created: 15.11.2019 10:45:08
 *  Author: Fabio Curman
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "fifo.h"


#define BUFFER_FULL 1
#define BUFFER_EMPTY 0

// Variables which are changed by interrupts must be declared as volatile.
volatile FIFO8_t buffer;

void usart_init(void){
	//Initialize the USART pins.
	USB_USART_PORT.DIR &= ~USB_USART_RX_PIN_bm;
	
	// Initialize USART and enable RXC interrupt.
	USB_USART_MODULE.CTRLA = USART_RXCINTLVL_LO_gc;
	USB_USART_MODULE.CTRLC = (USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc);
	USB_USART_MODULE.BAUDCTRLA = USB_USART_BSEL;
	USB_USART_MODULE.BAUDCTRLB = (USB_USART_BSCALE << USART_BSCALE_gp);
	USB_USART_MODULE.CTRLB = (USART_RXEN_bm | USART_TXEN_bm);
	
	// enable low-level interrupts.
	PMIC.CTRL |= PMIC_LOLVLEN_bm;
	CPU_SREG |= CPU_I_bm;
}


uint8_t usart_receive_complete(void){
		return FIFO_available(buffer);
}

uint8_t usart_receive(void){
	// Echo data if buffer is full.
	    cli();
		return FIFO8_read(buffer);
		sei();
}

ISR(USB_USART_RXC_vect){
	//store char in buffer
	FIFO8_write(buffer, USB_USART_MODULE.DATA);
}