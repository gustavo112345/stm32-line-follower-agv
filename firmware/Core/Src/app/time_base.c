/*
 * time_base.c
 *
 *  Created on: Nov 23, 2026
 *      Author: gubber
 */

#include "app/time_base.h"

volatile uint32_t tick = 0;

void SysTick_Handler(void)
{
	tick++;
}

