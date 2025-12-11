#ifndef __piloteIT_h
#define __piloteIT_h
#include "stm32f10x.h"

extern void (*USART1_handler_function)(void);
extern void (*USART2_handler_function)(void);
extern void (*USART3_handler_function)(void);

extern void (*T1_handler_function)(void);
extern void (*T2_handler_function)(void);
extern void (*T2_handler_function)(void);
extern void (*T3_handler_function)(void);

void InitTimerInterruption(TIM_TypeDef *TIMER, void (*function)(void), char prior);

void TIM1_UP_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);

extern void (*USART1_handler_function)(void);
extern void (*USART2_handler_function)(void);
extern void (*USART3_handler_function)(void);

void InitUSARTInterruption(USART_TypeDef *USART, void (*function)(void), char prior);

#endif