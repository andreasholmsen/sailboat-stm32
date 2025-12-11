#include "incremental-encoder.h"

/**
 * From a setting up timer, it configure TIM as a incremental encoder.
 *
 * @param TIM
 * @param tim_num
 * @param MAX
 */
void setup_encoder(TIM_TypeDef *TIM){
    /**
     * Its link the TIM with the channel to input the value of the encoder in it.
     */
	TIM->CCMR1 &= ~(3<<0); // (11<<0)
	TIM->CCMR1 |= (1 <<0); // CC1 channel is configured as input, IC1 is mapped on TI1
	TIM->CCMR1 &= ~(3<<8); //(11<<0)
	TIM->CCMR1 |= (1<< 8); // CC2 channel 
	
	
	/*
	CC1 channel configured as input:
	This bit determines if a capture of the counter value can actually be done into the input
	capture/compare register 1 (TIMx_CCR1) or not.
		0: Capture disabled.
		1: Capture enabled
	*/
	TIM->CCER &= ~(1<<1); // (0<<1)  Capture/Compare 1 output polarity :
	TIM->CCER &= ~(1<<5); // (0   Capture/Compare 2 output polarity :
	
	/*
	001: Encoder mode 1 - Counter counts up/down on TI2FP1 edge depending on TI1FP2
	level.
	010: Encoder mode 2 - Counter counts up/down on TI1FP2 edge depending on TI2FP1
	level.
	011: Encoder mode 3 - Counter counts up/down on both TI1FP1 and TI2FP2 edges
	*/
	TIM->SMCR |= (3<<0); //  (011<<0) SMS: Slave mode selection
	
}