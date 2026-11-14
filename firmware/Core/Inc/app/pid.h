/*
 * pid.h
 *
 *  Created on: 21/10/2026
 *      Author: Gustavo
 */

#ifndef PID_H_
#define PID_H_

struct PID_parameters {
	float kp;
	float ki;
	float kd;
	float integral;
	float prev_error;
	float setpoint;
};

float pid_controller(volatile struct PID_parameters *param, float current_value);

#endif /* PID_H_ */
