/*
 * cinematics.h
 *
 *  Created on: Nov 14, 2026
 *      Author: gusta
 */

#ifndef CINEMATICS_H_
#define CINEMATICS_H_

#include <drivers/hw_timers.h>

struct WheelVelocities
{
	float right;
	float left;
};

extern volatile struct WheelVelocities w_wheel_target;
void kinematics(volatile struct WheelVelocities *w_wheel_target ,float v_ref, float w_car_ref);

#endif /* CINEMATICS_H_ */
