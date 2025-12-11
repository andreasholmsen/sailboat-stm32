#include "timer.h"


void InitTimer(TIM_TypeDef* TIM, const uint16_t ARR, const uint16_t PSC){
		
    // Enable timer clocks. TIM1 advanced
    if (TIM == TIM1) {RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; TIM1->BDTR |= TIM_BDTR_MOE;}

    if (TIM == TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    if (TIM == TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    if (TIM == TIM4) RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    
    //Set Prescaler and Timer Period
    TIM->PSC = PSC;
    TIM->ARR = ARR;

    // 3. Generate an update event to load the registers
    TIM->EGR = TIM_EGR_UG;

    // Enable timer interrupt
    TIM->DIER |= TIM_DIER_UIE;


    // Enable Timer
    TIM->CR1 |= TIM_CR1_CEN; 
}

void StartTimer(TIM_TypeDef * TIM) {
    TIM->CR1 |= TIM_CR1_CEN;
}

void StopTimer(TIM_TypeDef * TIM) {
    TIM->CR1 &= ~TIM_CR1_CEN;
}

//Get overflow status
char get_UIF(TIM_TypeDef* TIM) {
    return (TIM->SR & TIM_SR_UIF) ? 1 : 0;
}

//Reset overflow flag
void reset_UIF(TIM_TypeDef* TIM) {
    TIM->SR &= ~TIM_SR_UIF;
}

//Perform function when overflow
void catch_UIF(TIM_TypeDef* TIM, void (*handle_func)(void)) {
    if (TIM->SR & TIM_SR_UIF) {
        handle_func();
        TIM->SR &= ~TIM_SR_UIF;
    }
}