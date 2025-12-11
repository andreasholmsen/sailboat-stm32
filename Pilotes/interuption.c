#include "interuption.h"

void (*T1_handler_function)(void) = 0;
void (*T2_handler_function)(void) = 0;
void (*T3_handler_function)(void) = 0;
void (*T4_handler_function)(void) = 0;
void (*USART1_handler_function)(void) = 0;
void (*USART2_handler_function)(void) = 0;
void (*USART3_handler_function)(void) = 0;


void InitTimerInterruption(TIM_TypeDef *TIMER,void (*function) (void), char prior) {
    if(TIMER == TIM1) {
		NVIC_EnableIRQ(TIM1_UP_IRQn);
		NVIC_SetPriority(TIM1_UP_IRQn, prior);
		T1_handler_function = function;
	} else if (TIMER==TIM2) {
		NVIC_EnableIRQ(TIM2_IRQn);
		NVIC_SetPriority(TIM2_IRQn, prior);
		T2_handler_function = function;
	} else if (TIMER==TIM3) {
		NVIC_EnableIRQ(TIM3_IRQn);
		NVIC_SetPriority(TIM3_IRQn, prior);
        T3_handler_function = function;
	} else if (TIMER==TIM4) {
		NVIC_EnableIRQ(TIM4_IRQn);
		NVIC_SetPriority(TIM4_IRQn, prior);
		T4_handler_function = function;
	}

    // Enable timer update interrupt
    TIMER->DIER |= TIM_DIER_UIE;
}


void InitUSARTInterruption(USART_TypeDef *USART, void (*function)(void), char prior) {
    if (USART == USART1) {
        NVIC_EnableIRQ(USART1_IRQn);
        NVIC_SetPriority(USART1_IRQn, prior);
        USART1_handler_function = function;
        USART1->CR1 |= USART_CR1_RXNEIE; // Enable RX interrupt
    } else if (USART == USART2) {
        NVIC_EnableIRQ(USART2_IRQn);
        NVIC_SetPriority(USART2_IRQn, prior);
        USART2_handler_function = function;
        USART2->CR1 |= USART_CR1_RXNEIE;
    } else if (USART == USART3) {
        NVIC_EnableIRQ(USART3_IRQn);
        NVIC_SetPriority(USART3_IRQn, prior);
        USART3_handler_function = function;
        USART3->CR1 |= USART_CR1_RXNEIE;
    }
}

//TIM1 UPDATE IRQHandler
void TIM1_UP_IRQHandler(void) {
    if (T1_handler_function) T1_handler_function();
    TIM1->SR &= ~TIM_SR_UIF; // Clear update interrupt flag
}

void TIM2_IRQHandler(void) {
    if (T2_handler_function) T2_handler_function();
    TIM2->SR &= ~TIM_SR_UIF;
}

void TIM3_IRQHandler(void) {
    if (T3_handler_function) T3_handler_function();
    TIM3->SR &= ~TIM_SR_UIF;
}

void TIM4_IRQHandler(void) {
    if (T4_handler_function) T4_handler_function();
    TIM4->SR &= ~TIM_SR_UIF;
}

void USART1_IRQHandler(void) {
    if (USART1_handler_function) USART1_handler_function();
}

void USART2_IRQHandler(void) {
    if (USART2_handler_function) USART2_handler_function();
}

void USART3_IRQHandler(void) {
    if (USART3_handler_function) USART3_handler_function();
}