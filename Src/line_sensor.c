/*
 * ir_array.c
 *
 *  Created on: 21/10/2026
 *      Author: Gustavo
 */

#include "line_sensor.h"
#include <stdint.h>

float update_line_position(volatile uint16_t *bufferADC){
	static const float weights[N_SENSORS] = {1000.0f, 2000.0f, 3000.0f, 4000.0f, 5000.0f};
	static const float max = 4096.0f;
	static const float min = 0.0f;
	static float last_position = 0.0f;
	float sum = 0.0f;
	float weight_sum = 0.0f;

	for(enum IR_sensor_array sensor_array = IR_FAR_RIGHT; sensor_array < N_SENSORS; sensor_array++){
		float normalized = (max - bufferADC[sensor_array]) / (max - min);
		sum += normalized;
		weight_sum += (normalized * weights[sensor_array]);
	}

	last_position = weight_sum / sum;
	return last_position;
}

