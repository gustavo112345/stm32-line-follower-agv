/*
 * time_base.h
 *
 *  Created on: Nov 23, 2026
 *      Author: gubber
 */

#ifndef TIME_BASE_H_
#define TIME_BASE_H_

#include <stdint.h>

extern volatile uint32_t tick;
void SysTick_Handler(void);

#endif /* TIME_BASE_H_ */
