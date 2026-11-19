/*
 * apply_pwm.c
 *
 *  Created on: Nov 18, 2026
 *      Author: gubber
 */
#include "app/apply_pwm.h"

void apply_pwm(struct WheelVelocities *velocity)
{
	const float v_max = 1.24f; //(700rpm)

	if (velocity->right > v_max) velocity->right = v_max;
	if (velocity->left > v_max) velocity->left = v_max;

	if (velocity->right < 0.0f) velocity->right = 0.0f;
	if (velocity->left < 0.0f)  velocity->left = 0.0f;

	uint16_t pwm_dir = (uint16_t)((velocity->right / v_max) * 3999.0f);
	uint16_t pwm_esq = (uint16_t)((velocity->left / v_max) * 3999.0f);

	TIM3->CCR1 = pwm_esq;
	TIM3->CCR2 = pwm_dir;
}
