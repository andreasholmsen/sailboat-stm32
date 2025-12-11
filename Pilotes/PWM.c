#include "PWM.h"

// Set AF-Push Pull
void InitPWM(TIM_TypeDef* TIM, float duty_cycle, char CH) {
    // Example: ARR and PSC are assumed to be set elsewhere (e.g., via InitTimer)
    // Enable PWM mode on the selected channel
    switch (CH) {
        case 1:
            TIM->CCMR1 &= ~(7 << 4);
            TIM->CCMR1 |= (6 << 4); // PWM mode 1, OC1M bits 6:4
            TIM->CCMR1 |= TIM_CCMR1_OC1PE;
            TIM->CCER  |= TIM_CCER_CC1E;
            TIM->CCR1 = (uint16_t)(TIM->ARR * duty_cycle);
            break;
        case 2:
            TIM->CCMR1 &= ~(7 << 12);
            TIM->CCMR1 |= (6 << 12); // PWM mode 1, OC2M bits 14:12
            TIM->CCMR1 |= TIM_CCMR1_OC2PE;
            TIM->CCER  |= TIM_CCER_CC2E;
            TIM->CCR2 = (uint16_t)(TIM->ARR * duty_cycle);
            break;
        case 3:
            TIM->CCMR2 &= ~(7 << 4);
            TIM->CCMR2 |= (6 << 4); // PWM mode 1, OC3M bits 6:4
            TIM->CCMR2 |= TIM_CCMR2_OC3PE;
            TIM->CCER  |= TIM_CCER_CC3E;
            TIM->CCR3 = (uint16_t)((float) TIM->ARR * duty_cycle);
            break;
        case 4:
            TIM->CCMR2 &= ~(7 << 12);
            TIM->CCMR2 |= (6 << 12); // PWM mode 1, OC4M bits 14:12
            TIM->CCMR2 |= TIM_CCMR2_OC4PE;
            TIM->CCER  |= TIM_CCER_CC4E;
            TIM->CCR4 = (uint16_t)(TIM->ARR * duty_cycle);
            break;
        default:
            break;
    }
    // Enable auto-reload preload
    TIM->CR1 |= TIM_CR1_ARPE;
    // Generate update event to load registers
    TIM->EGR = TIM_EGR_UG;
    // Enable counter
    TIM->CR1 |= TIM_CR1_CEN;
}

void PWMSetDuty(TIM_TypeDef* TIM, float duty, char CH) {
    switch (CH) {
        case 1:
            TIM->CCR1 = (uint16_t)(TIM->ARR * duty);
            break;
        case 2:
            TIM->CCR2 = (uint16_t)(TIM->ARR * duty);
            break;
        case 3:
            TIM->CCR3 = (uint16_t)(TIM->ARR * duty);
            break;
        case 4:
            TIM->CCR4 = (uint16_t)(TIM->ARR * duty);
            break;
        default:
            break;
    }
}