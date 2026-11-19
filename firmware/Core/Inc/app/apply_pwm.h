/*
 * apply_pwm.h
 *
 *  Created on: Nov 18, 2026
 *      Author: gubber
 */

#ifndef APPLY_PWM_H_
#define APPLY_PWM_H_

#include "app/kinematics.h"
#include "stm32f4xx.h"
#include "stdint.h"

void apply_pwm(struct WheelVelocities *velocity);

#endif /* APPLY_PWM_H_ */
