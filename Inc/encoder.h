/*
 * rpm.h
 *
 *  Created on: 21/10/2026
 *      Author: Gustavo
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <stdint.h>

enum dir_motor {
	LEFT_MOTOR,
	RIGHT_MOTOR,
	N_MOTORS
};

struct encoder_state {
	uint32_t tick_count[N_MOTORS];
	int32_t delta[N_MOTORS];
	uint32_t last_count[N_MOTORS];
	float RPM[N_MOTORS];
};

void calc_rpm (volatile struct encoder_state *encoders);

#endif /* ENCODER_H_ */
