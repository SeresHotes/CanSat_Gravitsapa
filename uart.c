#include "uart.h"

void UartInit()
{
	UCSR0B |= (1 << TXEN0)|(1 << RXEN0)|(1 << RXCIE0);
	int ubrr = 51;
	UBRR0L = (uint8_t)ubrr;
}

void UartWriteByte(uint8_t byte)
{
	while((UCSR0A & (1 << UDRE0)) == 0);
	UDR0 = byte;
}
uint8_t UartReadByte()
{
	while((UCSR0A & (1 << RXC0)) == 0);
	return UDR0;
}

int myPutChar(char value, FILE * stream)
{
	UartWriteByte(value);
	return 0;
}

FILE mystdout = FDEV_SETUP_STREAM(myPutChar, NULL, _FDEV_SETUP_WRITE);

void UartInitStdio()
{
	stdout = &mystdout;
}
