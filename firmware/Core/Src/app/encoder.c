/*
 * rpm.c
 *
 *  Created on: 21/10/2026
 *      Author: Gustavo
 */

#include "app/encoder.h"

#define ENCODER_PPR 836.0f
#define SAMPLE_TIME_S ((DT_MS) / 1000.0f)
#define RPM_CONV_FACTOR ((60.0f / SAMPLE_TIME_S) / ENCODER_PPR)
#define PI 3.14159265f
#define RPM_TO_RAD_S (2.0f * PI / 60.0f)

volatile struct encoder_state encoders = {0};

void update_encoders (volatile struct encoder_state *encoders)
{
	encoders->tick_count[LEFT_MOTOR]=TIM5->CNT;
	encoders->tick_count[RIGHT_MOTOR]=TIM2->CNT;

	for(enum dir_motor i = LEFT_MOTOR; i < N_MOTORS; i++)
	{
		encoders->delta[i] = (int32_t)(encoders->tick_count[i] - encoders->last_count[i]);
		encoders->RPM[i] = encoders->delta[i] * RPM_CONV_FACTOR;
		encoders->FILTERED_RPM[i] = (0.70f * encoders->RPM[i]) + (0.30f * encoders->FILTERED_RPM[i]);
		encoders->w_wheel[i] = encoders->FILTERED_RPM[i] * RPM_TO_RAD_S;
		encoders->last_count[i] = encoders->tick_count[i];
	}
}
