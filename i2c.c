#include <avr/io.h>

#include <stdint.h>

#include "i2c.h"
#include "uart.h"


#define ADDRESS 0x68

uint8_t i2cInit()
{
	printf("\nINIT\r\n");
	/////F_scl = 8000000/200 = 40kHz
	TWBR = 23;
	TWSR = (1 << TWPS0);
	//// Вкл.-
	TWCR = (1 << TWEN);// | (1 << TWEA);
	return 0;
}

uint8_t state()
{
	printf("STATE\r\n");
	while(!(TWCR & (1 << TWINT))){printf(" 0x%x",TWSR & 0b11111000);}
	return (TWSR & 0b11111000);
}

uint8_t i2cStart()
{
	printf("START\r\n");
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTA);
	uint8_t st = state();

	printf("Code after START: 0x%x\r\n",st);
	if(st == 0x08 || st == 0x10) return 0;
	return st;
}

uint8_t i2cStop()
{
	printf("STOP\r\n");
	TWCR = (1 << TWEN) | (1 << TWSTO) | (1 << TWINT);
	return 0;
}

uint8_t i2cWriteData(uint8_t *byte, uint8_t length)
{
	printf("WRITE DATA\r\n");
	for(int i = 0; i < length; i++)
	{
		TWDR = byte[i];
		TWCR = (1 << TWEN) | (1 << TWINT);

		uint8_t st = state();
		printf("Code after WRITE_DATA[%d]: 0x%x\r\n",i,st);

		if(st != 0x28) return st;
	}
	return 0;
}

uint8_t i2cReadData(uint8_t *byte, uint8_t length)
{
	printf("READ DATA\r\n");
	int i;
	for(i = 0; i < length; i++)
	{
		byte[i] = TWDR;
		TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);

		uint8_t st = state();
		printf("Code after READ_DATA[%d]: 0x%x\r\n",i,st);

		if(st != 0x50) return st;
	}
	return 0;
}



uint8_t i2cSendAddress(uint8_t direction)
{
	printf("SEND ADDRESS(%d)\r\n",direction);
	if(direction) direction = 1;
	TWDR = (ADDRESS << 1) | direction;
	TWCR |= (1 << TWINT);

	uint8_t st = state();
	printf("Code after SEND_ADDRESS(%d): 0x%x\r\n",direction,st);

	if(st == 0x40 || st == 0x18) return 0;
	return st;
}

uint8_t i2cSendData(uint8_t address,uint8_t *byte, uint8_t length)
{
	uint8_t t = 0;
	t = i2cStart(); 				if(t)goto ERROR;
	t = i2cSendAddress(0);			if(t)goto ERROR;
	t = i2cWriteData(&address,1);	if(t)goto ERROR;
	t = i2cWriteData(byte,length);	if(t)goto ERROR;
	t = i2cStop();					if(t)goto ERROR;
	return 0;

	//////ATTENTION!!! GOTO
	ERROR:
	{
		i2cStop();
		return t;
	}
}

uint8_t i2cRecieveData(uint8_t address,uint8_t *byte, uint8_t length)
{
	printf("RECIEVE DATA\r\n");
	uint8_t t = 0;
	t = i2cStart(); 				if(t)goto ERROR;
	t = i2cSendAddress(0);			if(t)goto ERROR;
	t = i2cWriteData(&address,1);	if(t)goto ERROR;

	t = i2cStart();					if(t)goto ERROR;
	t = i2cSendAddress(1);			if(t)goto ERROR;
	t = i2cReadData(byte,length);	if(t)goto ERROR;

	i2cStop();
	return 0;

	//////ATTENTION!!! GOTO
	ERROR:
	{
		i2cStop();
		return t;
	}
}












