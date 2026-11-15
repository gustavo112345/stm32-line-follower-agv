/*
 * cinematics.c
 *
 *  Created on: Nov 14, 2026
 *      Author: gusta
 */

#include <app/kinematics.h>

#define WHEELBASE_M 0.09f

struct WheelVelocities calculate_kinematics(float base_v_linear,float v_angular_pid){
	struct WheelVelocities velocity;

	float rotation_component = (WHEELBASE_M / 2.0f) * v_angular_pid;

	velocity.right = base_v_linear + rotation_component;
	velocity.left = base_v_linear - rotation_component;

	return velocity;
}
