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

int8_t activeState = RUNNING_TEXT_STATE;

void interrupt_init(void)
{
	
	/***** Initialize push-buttons and enable interrupts. *****/
	// Enable port interrupt 0 and 1.
	BUTTON_LOW_PORT.INTCTRL = PORT_INT0LVL_LO_gc | PORT_INT1LVL_LO_gc;
	// Pin 0 triggers interrupt 0
	BUTTON_LOW_PORT.INT0MASK = BUTTON0_PIN_bm;
	// Pin 1 triggers interrupt 1
	BUTTON_LOW_PORT.INT1MASK = BUTTON1_PIN_bm;
	// Trigger interrupt on falling edge
	BUTTON_LOW_PORT.PIN0CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
	BUTTON_LOW_PORT.PIN1CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;

	// Enable low-level interrupts.
	PMIC.CTRL |= PMIC_LOLVLEN_bm;
	CPU_SREG |= CPU_I_bm;

}

int8_t getActiveStatus() {
	return activeState;
}

/***** Port interrupt 0 *****/
// This interrupt service routine gets called whenever port interrupt 0 is thrown.
ISR(PORTD_INT0_vect)
{
	activeState = RUNNING_TEXT_STATE;
	
}

/***** Port interrupt 1 *****/
// This interrupt service routine gets called whenever port interrupt 1 is thrown.
ISR(PORTD_INT1_vect)
{
	activeState = COUNT_FROM_ZERO_TO_NINE;
	
}