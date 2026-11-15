/*
 * battery.c
 *
 *  Created on: Nov 14, 2026
 *      Author: gusta
 */

#include "app/battery.h"

float bat_voltage(volatile uint16_t *bufferADC){
	float bat_voltage;
	return bat_voltage = (bufferADC[5] * 8.4) / 3333;
}

float bat_percent(float bat_voltage){
	float bat_percent;
	return bat_percent = (bat_voltage * 100) / 8.4;
}
