/*
 * pid.c
 *
 *  Created on: 21/10/2026
 *      Author: Gustavo
 */

#include "app/pid.h"

#define MAX_V_ANGULAR 15.55f
#define MIN_V_ANGULAR -15.55f

volatile struct PID_parameters PID_angular =
{
		.kp = 0.485f,  // old 0.156f
		.ki = 0.0f,
		.kd = 0.0f,
		.integral = 0.0f,
		.prev_error = 0.0f,
		.setpoint = 0.0f,
};

float pid_controller(volatile struct PID_parameters *param, float current_value)
{
	float error = param->setpoint - current_value;
	float derivative = error - param->prev_error;
	param->integral += error;
	param->prev_error = error;

	float output = (param->kp * error) + (param->ki * param->integral) + (param->kd * derivative);

	if(output > MAX_V_ANGULAR) output = MAX_V_ANGULAR;
	if(output < MIN_V_ANGULAR) output = MIN_V_ANGULAR;

	return output;
}
