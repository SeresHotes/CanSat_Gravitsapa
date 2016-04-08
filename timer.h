/*
 * timer.h
 *
 *  Created on: 12 марта 2016 г.
 *      Author: developer
 */

#ifndef TIMER_H_
#define TIMER_H_

typedef struct
{
	uint16_t seconds;
	uint16_t subseconds;
} TimeData;

TimeData getTime();

void timerInit();

#endif /* TIMER_H_ */
