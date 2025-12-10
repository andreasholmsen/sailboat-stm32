#include "stm32f10x.h"
#include "MyGPIO.h"


int main ( void )
{
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;
	

	while (1)
	{
	}
}
