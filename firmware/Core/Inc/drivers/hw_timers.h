/*
 * hw_timers.h
 *
 *  Created on: Nov 14, 2026
 *      Author: gubber
 */

#ifndef HW_TIMERS_H_
#define HW_TIMERS_H_

#include "stm32f4xx.h"

#define TIM9_CLOCK_HZ 100000000.0f
#define TIM9_PSC 9999U
#define TIM9_ARR 49U

#define DT_MS (((TIM9_PSC + 1.0f) * (TIM9_ARR + 1.0f) * 1000.0f) / TIM9_CLOCK_HZ)

void Timers_Init(void);

#endif /* HW_TIMERS_H_ */
