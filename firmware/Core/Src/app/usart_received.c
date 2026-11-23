/*
 * usart_received.c
 *
 *  Created on: Nov 19, 2026
 *      Author: gubber
 */

#include "app/usart_received.h"

volatile uint16_t head;
static uint16_t tail = 0;
volatile uint8_t msg_received = 0;

void USART1_IRQHandler(void)
{
	if(USART1->SR & USART_SR_IDLE){
		uint32_t temp = USART1->SR;
		temp = USART1->DR;
		(void)temp;

		uint32_t NDTR = DMA2_Stream5->NDTR;
		head = RX_BUFFER_SIZE - NDTR;
		msg_received=1;

	}
}

void process_usart_command(void)
{
	uint8_t cmd = bufferRX[tail];
	tail = head;

	switch(cmd)
	{
	case '1':
		control_start();
		break;

	case '2':
		control_stop();
		break;

	case '+':
		v_ref += 0.05f;
		break;

	case '-':
		v_ref -= 0.05f;
		break;
	}
	msg_received = 0;
}
