/*
 * rpm.c
 *
 *  Created on: 21/10/2026
 *      Author: Gustavo
 */

#include "app/encoder.h"

#define ENCODER_PPR 836.0f
#define SAMPLE_TIME_S DT_MS / 1000.0f

volatile struct encoder_state encoders = {0};

void calc_rpm (volatile struct encoder_state *encoders)
{
	static const float RPM_CONV_FACTOR =  (60.0f / SAMPLE_TIME_S) / ENCODER_PPR;
	encoders->tick_count[LEFT_MOTOR]=TIM2->CNT;
	encoders->tick_count[RIGHT_MOTOR]=TIM5->CNT;

	for(enum dir_motor dir = LEFT_MOTOR; dir < N_MOTORS; dir++)
	{
		encoders->delta[dir] = (int32_t)(encoders->tick_count[dir] - encoders->last_count[dir]);
		encoders->RPM[dir] = (float) encoders->delta[dir] * RPM_CONV_FACTOR;
		encoders->FILTERED_RPM[dir] = (0.10f * encoders->RPM[dir]) + (0.90f * encoders->FILTERED_RPM[dir]);
		encoders->last_count[dir] = encoders->tick_count[dir];
	}
}
