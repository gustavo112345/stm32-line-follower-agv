/*
 * usart_transmit.c
 *
 *  Created on: Nov 14, 2026
 *      Author: gusta
 */


#include "app/usart_transmit.h"

void send_message(char *msg)
{
	if(DMA2_Stream7->CR & DMA_SxCR_EN) return;

	DMA2->HIFCR = DMA_HIFCR_CTCIF7;

	DMA2_Stream7->M0AR = (uint32_t)msg;
	DMA2_Stream7->NDTR = strlen(msg);

	DMA2_Stream7->CR |= DMA_SxCR_EN;
}

bool usart_tx_busy(void)
{
	if((DMA2_Stream7->CR & DMA_SxCR_EN) != 0)
	{
		return true;
	}
	return false;
}
