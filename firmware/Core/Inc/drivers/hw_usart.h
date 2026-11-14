/*
 * usart.h
 *
 *  Created on: Nov 14, 2026
 *      Author: gubber
 */

#ifndef HW_USART_H_
#define HW_USART_H_

#include <stdint.h>
#include "stm32f4xx.h"

extern uint8_t bufferTX[250]; //TAMANHO DO BUFFER TEM QUE SER definido para ser ALTERADO GLOBALMENTE DE UMA VEZ SO
extern uint8_t bufferRX[250]; //TAMANHO DO BUFFER TEM QUE SER definido para ser ALTERADO GLOBALMENTE DE UMA VEZ SO

void USART1_Init(void);

#endif /* HW_USART_H_ */
