/*
 * usart_transmit.c
 *
 *  Created on: Nov 14, 2026
 *      Author: gusta
 */


#include "app/usart_transmit.h"

uint8_t bufferTX[TX_BUFFER_SIZE];

void send_message(char *msg) {
	if(DMA2_Stream7->CR & DMA_SxCR_EN) return;

	DMA2->HIFCR = DMA_HIFCR_CTCIF7;

	DMA2_Stream7->M0AR = (uint32_t)bufferTX;
	DMA2_Stream7->NDTR = strlen((char*)bufferTX);

	DMA2_Stream7->CR |= DMA_SxCR_EN;

}
