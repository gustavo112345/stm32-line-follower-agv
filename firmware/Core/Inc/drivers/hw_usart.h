/*
 * usart.h
 *
 *  Created on: Nov 14, 2026
 *      Author: gubber
 */

#ifndef HW_USART_H_
#define HW_USART_H_

#include "stm32f4xx.h"
#include <stdint.h>

#define RX_BUFFER_SIZE 250U
extern uint8_t bufferRX[RX_BUFFER_SIZE];

void USART1_Init(void);

#endif /* HW_USART_H_ */
