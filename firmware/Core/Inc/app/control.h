/*
 * control.h
 *
 *  Created on: Nov 23, 2026
 *      Author: gubber
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "stm32f4xx.h"
#include <stdbool.h>

#include <drivers/hw_adc.h>

#include "app/line_sensor.h"
#include "app/pid.h"
#include "app/encoder.h"
#include "app/battery.h"
#include "app/kinematics.h"
#include "app/apply_pwm.h"
#include "app/speed_profile.h"

extern float v_ref;
extern volatile float v_bat;
void TIM1_BRK_TIM9_IRQHandler(void);
void control_update(void);
void control_start(void);
void control_stop(void);

#endif /* CONTROL_H_ */
