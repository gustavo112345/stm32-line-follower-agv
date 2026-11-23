/*
 * pid.h
 *
 *  Created on: 21/10/2026
 *      Author: Gustavo
 */

#ifndef PID_H_
#define PID_H_

struct PID_parameters
{
	float kp;
	float ki;
	float kd;
	float integral;
	float prev_error;
	float setpoint;
	float max_value;
	float min_value;
};

extern volatile struct PID_parameters PID_angular;
extern volatile struct PID_parameters PID_right_motor;
extern volatile struct PID_parameters PID_left_motor;

float pid_controller(volatile struct PID_parameters *param, float current_value, float setpoint);
void pid_reset(volatile struct PID_parameters *param);

#endif /* PID_H_ */
