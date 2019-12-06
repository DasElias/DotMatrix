#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <avr/io.h>

#define DISPLAY_RUNNING_TEXT 1
#define DISPLAY_NUMBERS 2
#define DISPLAY_CHARACTERS 3
#define DISPLAY_USART_PATTERN 4

void interrupt_init(void);
int8_t getActiveStatus();

#endif /* INTERRUPT_H_ */
