/*
 * pid.c
 *
 *  Created on: 21/10/2026
 *      Author: Gustavo
 */

#include "app/pid.h"

#define MAX_V_ANGULAR 5.0f
#define MIN_V_ANGULAR -5.0f

float pid_controller(volatile struct PID_parameters *param, float current_value)
{
	float error = param->setpoint - current_value;
	float derivative = error - param->prev_error;
	param->integral += error;
	param->prev_error = error;

	float output = (param->kp * error) + (param->ki * param->integral) + (param->kd * derivative);

	if(output > MAX_V_ANGULAR) output = 5.0f;
	if(output < MIN_V_ANGULAR) output = -5.0f;

	return output;
}
