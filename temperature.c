/*
 * temperature.c
 *
 *  Created on: 05 марта 2016 г.
 *      Author: developer
 */
#include "temperature.h"

uint16_t tempMesure()
{
	//uint8_t tRom[8];
	OneWireReset();
	OneWireWriteByte(0xCC);
	OneWireWriteByte(0x44);

	_delay_ms(1000);

	OneWireReset();
	OneWireWriteByte(0xCC);
	OneWireWriteByte(0xBE);

	uint8_t str[9];
	for(int i = 0; i < 9; i++)
	{
		str[i] = OneWireReadByte();
	}
	uint16_t temper16 = ((uint16_t)str[1] << 8) | str[0];
	//float retval = temper16 / 16.0f;

	return temper16;
}
