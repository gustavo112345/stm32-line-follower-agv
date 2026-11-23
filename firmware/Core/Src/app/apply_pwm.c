/*
 * apply_pwm.c
 *
 *  Created on: Nov 18, 2026
 *      Author: gubber
 */
#include "app/apply_pwm.h"

void apply_pwm(float right_motor_volt, float left_motor_volt, float v_bat)
{
    float duty_dir = right_motor_volt / v_bat;
    float duty_esq = left_motor_volt / v_bat;

    if (duty_dir > 1.0f) duty_dir = 1.0f;
    if (duty_dir < 0.0f) duty_dir = 0.0f;

    if (duty_esq > 1.0f) duty_esq = 1.0f;
    if (duty_esq < 0.0f) duty_esq = 0.0f;

    uint16_t pwm_dir = (uint16_t)(duty_dir * 3999.0f);
    uint16_t pwm_esq = (uint16_t)(duty_esq * 3999.0f);

    TIM3->CCR1 = pwm_esq;
    TIM3->CCR2 = pwm_dir;
}
