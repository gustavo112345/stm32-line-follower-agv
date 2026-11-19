/*
 * usart_received.h
 *
 *  Created on: Nov 19, 2026
 *      Author: gubber
 */

#ifndef USART_RECEIVED_H_
#define USART_RECEIVED_H_

#include "drivers/hw_usart.h"
#include "app/kinematics.h"
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"

extern volatile bool isRunning;
extern float base_v_linear;
extern volatile uint16_t head;
extern volatile uint8_t msg_received;

void process_usart_command(void);

#endif /* USART_RECEIVED_H_ */
