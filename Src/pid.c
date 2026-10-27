/*
 * pid.c
 *
 *  Created on: 21/10/2026
 *      Author: Gustavo
 */

#include "pid.h"

float pid_controller(volatile struct PID_parameters *param, float current_value){
	float error = param->setpoint - current_value;
	float derivative = error - param->prev_error;
	param->integral += error;
	param->prev_error = error;

	float output = (param->kp * error) + (param->ki * param->integral) + (param->kd * derivative);
	return output;
}
