/*
 * imu.h
 *
 *  Created on: 26 марта 2016 г.
 *      Author: developer
 */

#ifndef IMU_H_
#define IMU_H_

uint8_t imuInit();

uint8_t imuMesure(uint8_t * byte, uint8_t length);

#endif /* IMU_H_ */
