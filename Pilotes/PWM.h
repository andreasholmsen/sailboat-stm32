#ifndef __pilotePWM_h
#define __pilotePWM_h
#include "stm32f10x.h"

void InitPWM(TIM_TypeDef* TIM, float duty_cycle, char CH);
void PWMSetDuty(TIM_TypeDef* TIM, float duty, char CH);



#endif