/*
 * control.c
 *
 *  Created on: Nov 23, 2026
 *      Author: gubber
 */

#include "app/control.h"

volatile bool isRunning = false;
volatile float v_bat;
volatile float position;
volatile float w_car_ref;
volatile float right_motor_volt;
volatile float left_motor_volt;

void TIM1_BRK_TIM9_IRQHandler(void)
{
	if(TIM9->SR & TIM_SR_UIF)
	{
		TIM9->SR &= ~(TIM_SR_UIF);
		control_update();
	}
}

void control_update(void)
{
	v_bat = bat_voltage((bufferADC));
	update_encoders(&encoders);

	if(isRunning)
	{
		position = update_line_position(bufferADC);
		w_car_ref = pid_controller(&PID_angular, position, 0.0f);
		kinematics(&w_wheel_target,ramp_velocity(v_ref), w_car_ref);
		right_motor_volt = pid_controller(&PID_right_motor, encoders.w_wheel[RIGHT_MOTOR], w_wheel_target.right);
		left_motor_volt = pid_controller(&PID_left_motor, encoders.w_wheel[LEFT_MOTOR], w_wheel_target.left);
		apply_pwm(right_motor_volt, left_motor_volt, v_bat);
	}
}

void control_start(void)
{
	ramp_reset();
	pid_reset(&PID_angular);
	pid_reset(&PID_right_motor);
	pid_reset(&PID_left_motor);
	isRunning = true;
}

void control_stop(void)
{
	isRunning = false;
	apply_pwm(0.0f, 0.0f, v_bat);
}
