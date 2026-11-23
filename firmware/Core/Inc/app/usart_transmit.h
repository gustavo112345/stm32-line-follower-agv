/*
 * usart_transmit.h
 *
 *  Created on: Nov 14, 2026
 *      Author: gusta
 */

#ifndef USART_TRANSMIT_H_
#define USART_TRANSMIT_H_

#include "stm32f4xx.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

void send_message(char *msg);
bool usart_tx_busy(void);

#endif /* USART_TRANSMIT_H_ */
