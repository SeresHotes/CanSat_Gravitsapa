/*
 * radioModule.h
 *
 *  Created on: 16 марта 2016 г.
 *      Author: developer
 */

#ifndef RADIOMODULE_H_
#define RADIOMODULE_H_




#define TX_DATA_SIZE 30 // 1..31
#define RX_DATA_SIZE 30 // 1..31
#define DATA_SIZE TX_DATA_SIZE - 11

typedef struct
{
	uint8_t marker[2];
	uint8_t stRegister;
	uint16_t numberOfPacket;
	uint16_t time[2];
	uint8_t data[DATA_SIZE];
	uint16_t controlSum;
} Packet;

void rmInit();

void rmSendData(Packet * packet);

void rmSendByte(uint8_t byte);

void rmChangeMode(uint8_t mode);

#endif /* RADIOMODULE_H_ */
