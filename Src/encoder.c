/*
 * rpm.c
 *
 *  Created on: 21/10/2026
 *      Author: Gustavo
 */

#include "encoder.h"
#include "stm32f411xe.h"

#define ENCODER_PPR 836.0f
#define SAMPLE_TIME_S 0.01f

void calc_rpm (volatile struct encoder_state *encoders){
	static const float RPM_CONV_FACTOR =  (60.0f / SAMPLE_TIME_S) / ENCODER_PPR;
	encoders->tick_count[LEFT_MOTOR]=TIM2->CNT;
	encoders->tick_count[RIGHT_MOTOR]=TIM5->CNT;

	for(enum dir_motor dir = LEFT_MOTOR; dir < N_MOTORS; dir++){
		encoders->delta[dir] = (int32_t)(encoders->tick_count[dir] - encoders->last_count[dir]);
		encoders->RPM[dir] = (float) encoders->delta[dir] * RPM_CONV_FACTOR;
		encoders->last_count[dir] = encoders->tick_count[dir];
	}
}
