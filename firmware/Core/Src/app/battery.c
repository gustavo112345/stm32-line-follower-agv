/*
 * battery.c
 *
 *  Created on: Nov 14, 2026
 *      Author: gusta
 */

#include "app/battery.h"

#define BAT_MAX_VOLTAGE 8.40f
#define ADC_CH_VBAT 5
#define ADC_CALIB_MAX 3262.0f

const struct Battery batteryLUT[] =
{
		{8.40, 100},
		{7.89, 73},
		{7.71, 56},
		{7.49, 22},
		{7.37, 8},
		{7.22, 4},
		{7.02, 2},
		{6.78, 1},
		{6.41, 0},
};

float bat_voltage(volatile uint16_t *bufferADC)
{
	static float filtered_adc = 0.0f;
	float bat_voltage;

	if(filtered_adc == 0.0f)
	{
		filtered_adc = bufferADC[ADC_CH_VBAT];
	}

	filtered_adc = (0.01f * bufferADC[ADC_CH_VBAT]) + (0.99f * filtered_adc);
	return bat_voltage = (filtered_adc * BAT_MAX_VOLTAGE) / ADC_CALIB_MAX;
}

uint8_t bat_percent(const struct Battery *batteryLUT,float bat_voltage,uint8_t n)
{
	for (int i = 0; i < n-1; i++)
	{
		if(batteryLUT[i].voltage >= bat_voltage && batteryLUT[i+1].voltage <= bat_voltage)
		{
			float diff_voltage = bat_voltage - batteryLUT[i].voltage;
			float diff_n = batteryLUT[i+1].voltage - batteryLUT[i].voltage;

			return batteryLUT[i].battery_percent + (batteryLUT[i+1].battery_percent - batteryLUT[i].battery_percent) * (diff_voltage / diff_n);
		}
	}
	return 0;
}
