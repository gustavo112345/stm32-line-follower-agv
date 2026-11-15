/*
 * cinematics.h
 *
 *  Created on: Nov 14, 2026
 *      Author: gusta
 */

#ifndef CINEMATICS_H_
#define CINEMATICS_H_

struct WheelVelocities{
	float right;
	float left;
};

struct WheelVelocities calculate_kinematics(float base_v_linear, float v_angular_pid);

#endif /* CINEMATICS_H_ */
