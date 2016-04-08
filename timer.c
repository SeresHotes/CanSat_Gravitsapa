/*
 * timer.c
 *
 *  Created on: 12 марта 2016 г.
 *      Author: developer
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"

volatile uint16_t _seconds = 0;


ISR(TIMER1_COMPA_vect)
{
	_seconds++;
}



TimeData getTime()
{
	TimeData retval;
	cli();
	retval.subseconds = TCNT1;
	retval.seconds = _seconds;
	sei();
	return retval;
}

void timerInit()
{

	TCCR1A = 0;
	TCCR1B = (1 << WGM12);
	OCR1A = 31250;
	TIMSK = (1 << OCIE1A);
	TCCR1B |= (1 << CS12);
}
