#include "stm32f10x.h"
#include "GPIO.h"
#include "timer.h"
#include "PWM.h"
#include "UART.h"
#include "Navigation.h"
#include "weather-vane.h"

uint8_t tim_num = 2;
char val ;

int counter = 0;
void update(void) {
	counter = (counter +1)%20;
	//update_duty_cycle();
	if (!counter) UpdateNavigation();
}



int main ( void )
{
	// GPIOA clock enable | GPIOB clock enable | GPIO C clock enable
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;
	// Enable AFIO
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

	//InitGirouette(1);
	InitNavigation();
	
	//Setup update cycle
	InitTimer(TIM3, 1439, 999);
	StartTimer(TIM3);

	while (1)
	{
		catch_UIF(TIM3, update);
	}
}