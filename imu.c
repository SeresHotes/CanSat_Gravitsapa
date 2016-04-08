#include <avr/io.h>

#include <stdint.h>

#include "i2c.h"

uint8_t imuInit()
{
	return i2cInit();
}

uint8_t imuMesure(uint8_t *byte, uint8_t length)
{
	return i2cRecieveData(0x3B,byte, length);
}


