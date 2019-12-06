/*
 * interrupt.c
 *
 * Created: 15.11.2019 11:11:52
 *  Author: Tobias
 */ 

#include "interrupt.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include "board.h"

int8_t activeState = DISPLAY_RUNNING_TEXT; //Text beginnt mit dem bewegten Text

void interrupt_init(void)
{
	cli();
	
	BUTTON_LOW_PORT.DIRCLR = BUTTON0_PIN_bm | BUTTON1_PIN_bm | BUTTON2_PIN_bm | BUTTON3_PIN_bm;
	
	BUTTON0_PINCTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
	BUTTON1_PINCTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
	BUTTON2_PINCTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
	BUTTON3_PINCTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
	
	BUTTON_LOW_PORT.INTCTRL |= PORT_INT0LVL_LO_gc;
	
	PMIC.CTRL |= PMIC_LOLVLEN_bm;
		
	BUTTON_LOW_PORT.INT0MASK = BUTTON0_PIN_bm | BUTTON1_PIN_bm | BUTTON2_PIN_bm | BUTTON3_PIN_bm;
	
	sei();
}

	int8_t getActiveStatus() {
		return activeState;
	}	
	
ISR(PORTD_INT0_vect){
	if(!(BUTTON_LOW_PORT.IN & BUTTON0_PIN_bm))
	{
		activeState = DISPLAY_CHARACTERS;
	}
	
	if(!(BUTTON_LOW_PORT.IN & BUTTON1_PIN_bm))
	{
		activeState = DISPLAY_NUMBERS;
	}
	
	if(!(BUTTON_LOW_PORT.IN & BUTTON2_PIN_bm))
	{
		activeState = DISPLAY_RUNNING_TEXT;
	}
	
	if(!(BUTTON_LOW_PORT.IN & BUTTON3_PIN_bm))
	{
		activeState = DISPLAY_USART_PATTERN;
	}
}
	