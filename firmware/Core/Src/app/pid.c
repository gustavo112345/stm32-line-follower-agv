/*
 * pid.c
 *
 *  Created on: 21/10/2026
 *      Author: Gustavo
 */

#include "app/pid.h"

volatile struct PID_parameters PID_angular =
{
		.kp = 0.8f,
		.ki = 0.0f,
		.kd = 1.0f,
		.integral = 0.0f,
		.prev_error = 0.0f,
		.max_value = 12.0f,
		.min_value = -12.0f,
};

volatile struct PID_parameters PID_right_motor =
{
		.kp = 0.15f,
		.ki = 0.0f,
		.kd = 0.0f,
		.integral = 0.0f,
		.prev_error = 0.0f,
		.max_value = 8.4f,
		.min_value = 0.0f,
};

volatile struct PID_parameters PID_left_motor =
{
		.kp = 0.15f,
		.ki = 0.0f,
		.kd = 0.0f,
		.integral = 0.0f,
		.prev_error = 0.0f,
		.max_value = 8.4f,
		.min_value = 0.0f,
};

void pid_reset(volatile struct PID_parameters *param)
{
	param->integral = 0;
	param->prev_error = 0;
}

float pid_controller(volatile struct PID_parameters *param, float current_value, float setpoint)
{
	float error = setpoint - current_value;
	float derivative = error - param->prev_error;
	param->integral += error;
	param->prev_error = error;

	float output = (param->kp * error) + (param->ki * param->integral) + (param->kd * derivative);

	if(output > param->max_value) output = param->max_value;
	if(output < param->min_value) output = param->min_value;

	return output;
}
