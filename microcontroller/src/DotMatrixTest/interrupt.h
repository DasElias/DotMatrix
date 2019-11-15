#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <avr/io.h>

#define RUNNING_TEXT_STATE 1
#define COUNT_FROM_ZERO_TO_NINE 2

void interrupt_init(void);
int8_t getActiveStatus();

#endif /* INTERRUPT_H_ */
