#include "GPIO.h"

void InitGPIO(GPIO_TypeDef *GPIO, char BROCHE, char CONFIG) {
	if (GPIO==GPIOA) RCC->APB2ENR |= (0x01 << 2);
	if (GPIO==GPIOB) RCC->APB2ENR |= (0x01 << 3);
	if (GPIO==GPIOC) RCC->APB2ENR |= (0x01 << 4);
	
	// Define register space
 	volatile uint32_t * reg;
  uint8_t shift;

	if (BROCHE < 8) {
		reg = &(GPIO->CRL);
		shift = BROCHE*4;
	} else {
		reg = &(GPIO->CRH);
		shift = (BROCHE - 8) * 4;
	}

	 // Clear and set new configuration
    *reg &= ~(0xF << shift);
    *reg |= ((CONFIG & 0xF) << shift);
}

char ReadBroche(GPIO_TypeDef * GPIO, char BROCHE) {
	return (GPIO->IDR>>BROCHE) & 0x1;
}

void SetBroche(GPIO_TypeDef * GPIO, char BROCHE) {
	GPIO->BSRR = (1<<BROCHE);
}

void ResetBroche(GPIO_TypeDef * GPIO, char BROCHE) {
	GPIO->BSRR = (1<<(BROCHE+16));
}