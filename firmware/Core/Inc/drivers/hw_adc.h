/*
 * adc.h
 *
 *  Created on: Nov 14, 2026
 *      Author: gubber
 */

#ifndef HW_ADC_H_
#define HW_ADC_H_

#include <stdint.h>
#include "stm32f411xe.h"

extern volatile uint16_t bufferADC[6];

void ADC_Init(void);

#endif /* HW_ADC_H_ */
