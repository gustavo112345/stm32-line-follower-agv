/*
 * ir_array.c
 *
 *  Created on: 21/10/2026
 *      Author: Gustavo
 */

#include "app/line_sensor.h"

#define MAX_ADC_READ 3900.0f

float update_line_position(volatile uint16_t *bufferADC)
{
	static const float min_adc_read[N_SENSORS] = {1700.0f, 1400.0f, 1500.0f, 1750.0f, 1800.0f};
	static const float weights[N_SENSORS] = {-32.0f, -16.0f, 0.0f, 16.0f, 32.0f};
	static float last_position;
	float sum = 0.0f;
	float weight_sum = 0.0f;

	for(enum IR_sensor_array i = IR_FAR_RIGHT; i < N_SENSORS; i++)
	{
		float normalized = (MAX_ADC_READ - bufferADC[i]) / (MAX_ADC_READ - min_adc_read[i]);

		if(normalized < 0.1f)  // deadzone para eliminar ruido branco
		{
			normalized = 0.0f;
		}
		else if(normalized > 1.0f)
		{
			normalized = 1.0f;
		}

		sum += normalized;
		weight_sum += (normalized * weights[i]);
	}

	if(sum < 0.4f) return last_position;

	float position = weight_sum / sum;
	last_position = position;

	return position;
}

