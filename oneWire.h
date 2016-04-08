
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

void OneWireInit();
void OneWireWriteByte(uint8_t byte);
uint8_t OneWireReadByte();
int OneWireReset();

#endif /* ONEWIRE_H_ */
