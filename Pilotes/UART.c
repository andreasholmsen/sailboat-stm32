#include "UART.h"



/*
USART1:
    TX: PA9 AF PP
    RX: PA10 INPUT FLOATING

USART2:
    TX: PA2 AF PP
    RX: PA3 INPUT FLOATING

USART3:
    TX: PB10 AF PP
    RX: PB11 INPUT FLOATING
*/

void InitUSART(USART_TypeDef *USART, const uint32_t baudRate) {
    // 1. Enable clocks
    if (USART == USART1) {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    } else if (USART == USART2) {
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    } else if (USART == USART3) {
        RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    }

    // 3. Set baud rate (assuming 72MHz PCLK for USART1, 36MHz for USART2/3)
    int freq = 72000000;
		if (USART==USART1) USART->BRR = freq/baudRate;
		else USART->BRR = (freq/2)/baudRate;

    // 4. Enable USART, TX, RX
    USART->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void putChar(USART_TypeDef *USART, char c) {
    // Wait until transmit data register is empty
    while (!(USART->SR & USART_SR_TXE));
    USART->DR = c;
}

char readChar(USART_TypeDef *USART) {
    // Wait until data is received
    //while (!(USART->SR & USART_SR_RXNE));
    return USART->DR;
}