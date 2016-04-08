/*
 * i2c.h
 *
 *  Created on: 26 марта 2016 г.
 *      Author: developer
 */

#ifndef I2C_H_
#define I2C_H_

uint8_t i2cInit();

uint8_t i2cRecieveData(uint8_t address,uint8_t *byte, uint8_t length);

uint8_t i2cSendData(uint8_t address,uint8_t *byte, uint8_t length);

#endif /* I2C_H_ */
