#ifndef __piloteUART_h
#define __piloteUART_h

#include <stdio.h>
#include "stm32f10x.h"
#include "GPIO.h"

void InitUSART(USART_TypeDef *USART, const uint32_t baudRate);
void putChar(USART_TypeDef *USART, char c);
char readChar(USART_TypeDef *USART);

#endif