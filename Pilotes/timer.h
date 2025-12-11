#ifndef __piloteTIMER_h
#define __piloteTIMER_h
#include "stm32f10x.h"

void InitTimer(TIM_TypeDef* TIM, const uint16_t ARR, const uint16_t PSC);
void StartTimer(TIM_TypeDef * TIM);
void StopTimer(TIM_TypeDef * TIM);

char get_UIF(TIM_TypeDef* TIM);
void reset_UIF(TIM_TypeDef* TIM);
void catch_UIF(TIM_TypeDef* TIM, void (*handle_func)(void));

#endif