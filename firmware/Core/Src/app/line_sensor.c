/*
 * ir_array.c
 *
 *  Created on: 21/10/2026
 *      Author: Gustavo
 */

#include "app/line_sensor.h"

#define MAX_ADC_READ 3900.0f
#define MIN_ADC_READ 1500.0f

float update_line_position(volatile uint16_t *bufferADC)
{
	static const float weights[N_SENSORS] = {-32.0f, -16.0f, 0.0f, 16.0f, 32.0f};
	float position;
	static float last_position;
	float sum = 0.0f;
	float weight_sum = 0.0f;
	uint8_t lost_sensor = 0;

	for(enum IR_sensor_array sensor_array = IR_FAR_RIGHT; sensor_array < N_SENSORS; sensor_array++)
	{
		float normalized = (MAX_ADC_READ - bufferADC[sensor_array]) / (MAX_ADC_READ - MIN_ADC_READ);

		if(normalized < 0.0f)
		{
			normalized = 0.0f;
		}
		else if(normalized > 1.0f)
		{
			normalized = 1.0f;
		}

		if(normalized <= 0.5) lost_sensor++;

		sum += normalized;
		weight_sum += (normalized * weights[sensor_array]);
	}

	if(lost_sensor == 5) return last_position;

	position = weight_sum / sum;
	last_position = position;

	return position;
}

