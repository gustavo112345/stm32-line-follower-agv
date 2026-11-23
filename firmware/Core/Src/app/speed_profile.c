/*
 * speed_profile.c
 *
 *  Created on: Nov 23, 2026
 *      Author: gubber
 */

#include "app/speed_profile.h"

#define SAMPLE_TIME_S ((DT_MS) / 1000.0f)
#define V_START 0.25f
#define ACCEL 0.5f

static float v = V_START;

void ramp_reset(void)
{
	v = V_START;
}

float ramp_velocity(float v_ref)
{
	v += ACCEL * SAMPLE_TIME_S;

	if(v > v_ref)
	{
		v = v_ref;
	}

	return v;
}
