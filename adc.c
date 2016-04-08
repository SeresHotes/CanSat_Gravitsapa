#include "adc.h"



void AdcInit()
{
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

uint16_t AdcRead()
{
	ADCSRA |= (1 << ADSC);
	while((ADCSRA & (1 << ADIF)) == 0);
	uint16_t retval = ADC;
	ADCSRA |= (1 << ADIF);

	return retval;
}
