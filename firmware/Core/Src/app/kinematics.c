/*
 * cinematics.c
 *
 *  Created on: Nov 14, 2026
 *      Author: gusta
 */

#include <app/kinematics.h>

#define WHEELBASE_M 0.09f
#define RAMP_TIME_MS 7500

float v_linear_start = 0.25f;

struct WheelVelocities calculate_kinematics(float base_v_linear,float v_angular_pid)
{
	const float ramp_step = (base_v_linear - v_linear_start) / (RAMP_TIME_MS / DT_MS);
	struct WheelVelocities velocity;

	float rotation_component = (WHEELBASE_M / 2.0f) * v_angular_pid;

	velocity.right = v_linear_start + rotation_component;
	velocity.left = v_linear_start - rotation_component;

	if(v_linear_start < base_v_linear)
	{
		if(v_linear_start < (base_v_linear / 2))
		{
			v_linear_start += ramp_step;
		}
		else
		{
			v_linear_start += (32 * ramp_step);
		}

		if(v_linear_start > base_v_linear)
		{
			v_linear_start = base_v_linear;
		}
	}
	else if(v_linear_start > base_v_linear)
		{
			v_linear_start = base_v_linear;
		}

	return velocity;
}
