/*
 * hardware.c
 *
 *  Created on: Nov 14, 2026
 *      Author: gubber
 */

#include <drivers/hardware.h>
#include <drivers/hw_adc.h>
#include <drivers/hw_encoders.h>
#include <drivers/hw_motor.h>
#include <drivers/hw_system_clock.h>
#include <drivers/hw_timers.h>
#include <drivers/hw_usart.h>

void Hardware_Init(void) {

	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2)); // FPU INIT

    SystemClock_Init();
    Timers_Init();
    ADC_Init();
    USART1_Init();
    Encoders_Init();
    Motor_Init();

    // ENABLE ALL PERIPHERALS
    TIM4->CR1 |= TIM_CR1_CEN;          // START PWM 1HZ LED (TIM4)
    DMA2_Stream0->CR |= DMA_SxCR_EN;   // START DMA2_Stream0 (ADC1)
    ADC1->CR2 |= ADC_CR2_SWSTART;      // START ADC CONVERSIONS
    TIM5->CR1 |= TIM_CR1_CEN;          // START COUNT ENCODER 2 (TIM5)
    TIM2->CR1 |= TIM_CR1_CEN;          // START COUNT ENCODER 1 (TIM2)
    TIM3->CR1 |= TIM_CR1_CEN;          // START PWM DRIVER MOTOR (TIM3)
    USART1->CR1 |= USART_CR1_UE;       // START USART1
    //DMA2_Stream7->CR |= DMA_SxCR_EN; // START DMA2_Stream7 (USAR1_TX)
    DMA2_Stream5->CR |= DMA_SxCR_EN;   // START DMA2_Stream5 (USAR1_RX)

    TIM9->CR1 |= TIM_CR1_CEN;          // START INTERRUPT FOR PID CALCULATIONS
    SysTick_Config(100000);
}
