#include <stdio.h>

#include "radioModule.h"
#include "uart.h"


#define RM_DDR DDRB
#define RM_PORT PORTB
#define RM_PIN PINB
#define CNFG 0
#define RTS 1
#define CTC 2
#define DR1 3
#define DR2 4
#define PD 5

#define FREQ 433.1
#define FREQ_VALUE (FREQ - 422.4)*10
#define TX_POWER 0 ///0.-10	  1.-2	 2.+6	3.+10
#define TX_DATA_SIZE 30 // 1..31
#define RX_DATA_SIZE 30 // 1..31

#define SetOne(a) |=(1<<a)
#define SetZero(a) &=~(1<<a)

void rmSendData(Packet * packet)
{


	//RM_PORT SetZero(RTS);
	uint8_t *data = (uint8_t*)packet;
	int i = 0;
	for(;i < sizeof(Packet);i++)
	{
		while((RM_PIN & (1 << CTC)) == 1);
		UartWriteByte(data[i]);
	}
	//RM_PORT SetOne(RTS);
}

void rmSendByte(uint8_t byte)
{
	while((RM_PIN & (1 << CTC)) == 1);
	//RM_PORT SetZero(RTS);
	UartWriteByte(byte);
	//RM_PORT SetOne(RTS);

}

void rmChangeMode(uint8_t mode)
{
	if(mode == 0) RM_PORT SetZero(PD);
	else RM_PORT SetOne(PD);
}


void rmInit()
{
	RM_DDR SetZero(CTC);

	RM_PORT SetZero(RTS);
	RM_DDR SetOne(RTS);
	/*//// BAUD = 9600
	RM_PORT SetOne(DR1);
	RM_DDR SetOne(DR1);
	RM_PORT SetZero(DR2);
	RM_DDR SetOne(DR2);*/

	//Config
	RM_PORT SetOne(CNFG);
	RM_DDR SetOne(CNFG);

	///// Activate RM
	RM_PORT SetZero(PD);
	RM_DDR SetOne(PD);

	while((RM_PIN & (1 << CTC)) == 1);
	int i;
	RM_PORT SetZero(CNFG);
	for(i = 0; i< 4; i++)
	{
		while((RM_PIN & (1 << CTC)) == 1);
		UartWriteByte(0);
	}
	RM_PORT SetOne(CNFG);




	RM_PORT SetZero(PD);

}














