
#include "oneWire.h"

#define ONE_WIRE_PORT PORTC
#define ONE_WIRE_PPIN PINC
#define ONE_WIRE_DDR DDRC
#define ONE_WIRE_PIN 0

void OneWireInit()
{
	ONE_WIRE_PORT &= ~(1 << ONE_WIRE_PIN);
	ONE_WIRE_DDR &= ~(1 << ONE_WIRE_PIN);
}
void OneWireSetBusZero()
{
	ONE_WIRE_DDR |= (1 << ONE_WIRE_PIN);
}
void OneWireSetBusOne()
{
	ONE_WIRE_DDR &= ~(1 << ONE_WIRE_PIN);
}
int OneWireReadBus()
{
	return ONE_WIRE_PPIN & (1 << ONE_WIRE_PIN);
}
int OneWireReset()
{
	OneWireSetBusZero();
	_delay_us(500);
	OneWireSetBusOne();
	_delay_us(10);

	int isSomeoneHere = 0;
	for (int i = 0; i < 480; i++)
	{
		if (OneWireReadBus() == 0)
			isSomeoneHere = 1;

		_delay_us(1);
	}

	return isSomeoneHere;
}
void OneWireWriteBit(int value)
{
	OneWireSetBusZero();
	_delay_us(2);
	if (value != 0)
	{
		OneWireSetBusOne();
	}

	_delay_us(60);
	OneWireSetBusOne();
}
void OneWireWriteByte(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		uint8_t bit = (1 << i) & byte;
		OneWireWriteBit(bit);
	}
}
int OneWireReadBit()
{
	OneWireSetBusZero();
	_delay_us(2);
	OneWireSetBusOne();
	_delay_us(8);
	int retval = OneWireReadBus();
	_delay_us(30);
	return retval;
}
uint8_t OneWireReadByte()
{
	uint8_t retval = 0;
	for (uint8_t i = 0; i < 8; i++)
	{
		uint8_t bit = OneWireReadBit();
		if (bit != 0) { bit = 1;}
		retval |= (bit << i);
	}
	return retval;
}

