#include "Navigation.h"


signed char USART3Input;
float rapportCyclique;

//Handler for USART3. Fetches USART3 value
 void readUART3Handler(void) {
	USART3Input = readChar(USART3); // Read value from USART3
}

//Takes "USART3Input" and updates direction
void UpdateNavigation() {
	signed char local_USART3Input = USART3Input;
	rapportCyclique = fabsf((float)local_USART3Input) / 100.0f; // Add rapport Cyclique
	
	//If positive value, direction <- 0, else 1
	if (local_USART3Input >= 0) ResetBroche(GPIOA, 9);
	else SetBroche(GPIOA, 9);

	// Update PWM duty cycle
	PWMSetDuty(TIM1, rapportCyclique, 1);
}

void InitNavigation(void) {
    //Setup pins for use
	InitGPIO(GPIOA, 9,GPIO_MODE_OUTPUT_PP_2MHZ); // PA9 setup for direction bit
	InitGPIO(GPIOA, 8,GPIO_MODE_AF_PP_2MHZ); // PA8 for TIM1 CH1
	
	InitGPIO(GPIOB, 11,GPIO_MODE_FLOATING_INPUT); // PB11 for RX register of USART3.
	InitGPIO(GPIOB, 10, GPIO_MODE_AF_PP_2MHZ); // PB10 for TX register of USART3.
	
	//setup the USART
	InitUSART(USART3, 9600); // USART3 setup
	InitUSARTInterruption(USART3, readUART3Handler, 3); // Bind the readUART3Handler, priority 1
	
	InitTimer(TIM1, 359, 9); // setup TIM1 20kHz
	InitPWM(TIM1, 0.0, 1); // PWM setup: TIM1, RapportCyqlique = 0.0 and on channel 1
	StartTimer(TIM1); // Start the timer
	
	//Setup timer for update_direction interval
	InitTimer(TIM3, 1999, 7199); // Setup TIM3, 200ms
	StartTimer(TIM3);
	InitTimerInterruption(TIM3, UpdateNavigation, 1); // binds timer interval to update_direction

};