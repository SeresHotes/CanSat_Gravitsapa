
#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"
#include "oneWire.h"
#include "uart.h"
#include "temperature.h"
#include "timer.h"
#include "radioModule.h"
#include "imu.h"

#define LED_PORT 3




void LedInit()
{
	DDRG |= (1 << LED_PORT);
	PORTG &= ~(1 << LED_PORT);
}
void LightLed (int value)
{
	if (value != 0)
		PORTG |= (1 << LED_PORT);
	else
		PORTG &= ~(1 << LED_PORT);
}




int main()
{

	//OneWireInit();
	LedInit();
	UartInit();
	//AdcInit();
	UartInitStdio();
	//timerInit();
	LightLed(1);
	imuInit();
	//char ledTrigger = 0;
	//uint16_t count = 0;
	//uint16_t timeL = 0, timeH = 0;
	//rmInit();

	//rmChangeMode(0);

	//uint8_t i = 0;
	while(1)
	{
		int i;
		uint8_t byte[6];
		uint8_t code = imuMesure(byte,6);
		int16_t ttt = ((byte[0] << 8) | byte[0]);
		if(!code)
			for(i = 0; i < 6; i++)
				printf("Data[%d]: %d\t",i,byte[i]);
		else
			printf("ERROR: 0x%x",code);
		printf("\r\n\n\n");
		/*Packet packet;
		packet.marker[0] = 0xFF;
		packet.marker[1] = 0xFF;
		packet.numberOfPacket = count++;
		packet.stRegister = 't';
		uint16_t mesval;
		mesval = measureTemper();
		packet.data[0] = (uint8_t)mesval;
		packet.data[1] = (uint8_t)(mesval >> 8);
		mesval = AdcRead();
		packet.data[2] = (uint8_t)mesval;
		packet.data[3] = (uint8_t)(mesval >> 8);
		packet.time[0] = timeL;
		packet.time[1] = timeH;
		packet.controlSum = 0;

		uint16_t packSize = sizeof(Packet);
		uint8_t * ptr = (uint8_t*)&packet;


		int i = 0;
		for(;i<packSize - sizeof(packet.controlSum);i++)
		{
			packet.controlSum += ptr[i];
		}
		sendRmData(&packet);

		uint16_t timeTmp = timeL + 1000;
		if(timeL > timeTmp)
			timeH += 1;
		timeL = timeTmp;*/
		//rmSendByte(i++);
	}

	return 0;
}


