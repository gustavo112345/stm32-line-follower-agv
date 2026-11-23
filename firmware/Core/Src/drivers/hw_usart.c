/*
 * usart.c
 *
 *  Created on: Nov 14, 2026
 *      Author: gubber
 */


#include <drivers/hw_usart.h>

uint8_t bufferRX[RX_BUFFER_SIZE];

void USART1_Init(void) {
    //CONFIG USART
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    GPIOA->MODER &= ~(GPIO_MODER_MODER9 | GPIO_MODER_MODER10);
    GPIOA->MODER |= (GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1);
    GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL9 | GPIO_AFRH_AFSEL10);
    GPIOA->AFR[1] |= ((7U << GPIO_AFRH_AFSEL9_Pos) | (7U << GPIO_AFRH_AFSEL10_Pos));

    USART1->BRR = 0x364U;
    USART1->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_IDLEIE);
    USART1->CR3 |= (USART_CR3_DMAT | USART_CR3_DMAR);
    NVIC_EnableIRQ(USART1_IRQn);

    //CONFIG DMA2 (USART1TX)
    DMA2_Stream7->CR &= ~(DMA_SxCR_EN);
    while(DMA2_Stream7->CR & DMA_SxCR_EN);
    DMA2_Stream7->PAR = (uint32_t) &USART1->DR;
    DMA2_Stream7->CR &= ~(DMA_SxCR_CHSEL | DMA_SxCR_MSIZE | DMA_SxCR_PSIZE | DMA_SxCR_DIR | DMA_SxCR_MINC);
    DMA2_Stream7->CR |= ((4U << DMA_SxCR_CHSEL_Pos) | DMA_SxCR_MINC | (1U << DMA_SxCR_DIR_Pos));

    //CONFIG DMA2 (USART1RX)
    DMA2_Stream5->CR &= ~(DMA_SxCR_EN);
    while(DMA2_Stream5->CR & DMA_SxCR_EN);
    DMA2_Stream5->PAR = (uint32_t) &USART1->DR;
    DMA2_Stream5->M0AR = (uint32_t) bufferRX;
    DMA2_Stream5->NDTR = RX_BUFFER_SIZE;
    DMA2_Stream5->CR &= ~(DMA_SxCR_CHSEL | DMA_SxCR_MSIZE | DMA_SxCR_PSIZE | DMA_SxCR_DIR | DMA_SxCR_MINC);
    DMA2_Stream5->CR |= ((4U << DMA_SxCR_CHSEL_Pos) | DMA_SxCR_MINC | DMA_SxCR_CIRC);
}
