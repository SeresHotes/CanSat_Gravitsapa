#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>


void UartInit();
void UartWriteByte(uint8_t byte);
uint8_t UartReadByte();
void UartInitStdio();
inline void UartWriteString(char* str)
{
	while(*str)
	{
		UartWriteByte(*str);
		str++;
	}
}



#endif /* UART_H_ */
