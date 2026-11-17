/*
 * battery.h
 *
 *  Created on: Nov 14, 2026
 *      Author: gusta
 */

#ifndef BATTERY_H_
#define BATTERY_H_

#include <stdint.h>

#define LUT_SIZE 9

struct Battery
{
	float voltage;
	uint8_t battery_percent;
};

extern const struct Battery batteryLUT[LUT_SIZE];

float bat_voltage(volatile uint16_t *bufferADC);
uint8_t bat_percent(const struct Battery *batteryLUT,float bat_voltage,uint8_t n);

#endif /* BATTERY_H_ */
