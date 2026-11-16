/*
 * battery.h
 *
 *  Created on: Nov 14, 2026
 *      Author: gusta
 */

#ifndef BATTERY_H_
#define BATTERY_H_

#include <stdint.h>

float bat_voltage(volatile uint16_t *bufferADC);
int bat_percent(float bat_voltage);

#endif /* BATTERY_H_ */
