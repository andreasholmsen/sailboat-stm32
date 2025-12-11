#include "stm32f10x.h"
#include "GPIO.h"
#include "timer.h"
#include "PWM.h"
#include "UART.h"
#include "Navigation.h"

int main ( void )
{
	// GPIOA clock enable | GPIOB clock enable | GPIO C clock enable
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;
	// Enable AFIO
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

	
	InitNavigation();
	
	while (1)
	{
		
		
	}
}
