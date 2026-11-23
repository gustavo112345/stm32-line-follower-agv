/*
 * cinematics.c
 *
 *  Created on: Nov 14, 2026
 *      Author: gusta
 */

#include <app/kinematics.h>

#define WHEELBASE_M 0.09f
#define WHEEL_RADIUS_M 0.017f

volatile struct WheelVelocities w_wheel_target;

void kinematics(volatile struct WheelVelocities *w_wheel_target  ,float v_ref, float w_car_ref)
{
	float rotation_component = (WHEELBASE_M / 2.0f) * w_car_ref;

	w_wheel_target->right = (v_ref + rotation_component) / WHEEL_RADIUS_M;
	w_wheel_target->left = (v_ref - rotation_component) / WHEEL_RADIUS_M;
}
