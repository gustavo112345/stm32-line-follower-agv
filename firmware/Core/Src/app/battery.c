/*
 * battery.c
 *
 *  Created on: Nov 14, 2026
 *      Author: gusta
 */

#include "app/battery.h"

#define BAT_MAX_VOLTAGE 8.4f
#define ADC_CH_VBAT 5
#define ADC_CALIB_MAX 3262.0f

float bat_voltage(volatile uint16_t *bufferADC){
	static float filtered_adc = 0.0f;
	float bat_voltage;

	if(filtered_adc == 0.0f){
		filtered_adc = bufferADC[ADC_CH_VBAT];
	}

	filtered_adc = (0.01f * bufferADC[ADC_CH_VBAT]) + (0.99f * filtered_adc);
	return bat_voltage = (filtered_adc * BAT_MAX_VOLTAGE) / ADC_CALIB_MAX;
}

int bat_percent(float bat_voltage){
	float bat_percent;
	return bat_percent = (bat_voltage * 100) / 8.4;
}
