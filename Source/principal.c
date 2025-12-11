#include "stm32f10x.h"
#include "GPIO.h"
#include "timer.h"
#include "PWM.h"
#include "UART.h"
#include "Navigation.h"
#include "weather-vane.h"

uint8_t tim_num = 2;
char val ;

void update() {
	update_duty_cycle();
	UpdateNavigation();
}



int main ( void )
{
	// GPIOA clock enable | GPIOB clock enable | GPIO C clock enable
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;
	// Enable AFIO
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

	InitGirouette(0);
	InitNavigation();
	
	
	//Setup update cycle
	InitTimer(TIM1, 3599, 9);
	StartTimer(TIM1);

	while (1)
	{
		catch_UIF(TIM1, update);
	}
}