/*
 * speed_profile.h
 *
 *  Created on: Nov 23, 2026
 *      Author: gubber
 */

#ifndef SPEED_PROFILE_H_
#define SPEED_PROFILE_H_

#include "drivers/hw_timers.h"

float ramp_velocity(float v_ref);
void ramp_reset(void);

#endif /* SPEED_PROFILE_H_ */
