#ifndef __piloteGPIO_h
#define __piloteGPIO_h

#include "stm32f10x.h"

/*/////////////////////////////////////////////////////////////////
COMPLETE CONFIG
*//////////////////////////////////////////////////////////////////

#define GPIO_MODE_ANALOG           0x0  // MODE=00, CNF=00
#define GPIO_MODE_FLOATING_INPUT   0x4  // MODE=00, CNF=01
#define GPIO_MODE_INPUT_PU_PD      0x8  // MODE=00, CNF=10

#define GPIO_MODE_OUTPUT_PP_2MHZ   0x2  // MODE=10, CNF=00
#define GPIO_MODE_OUTPUT_OD_2MHZ   0x6  // MODE=10, CNF=01
#define GPIO_MODE_AF_PP_2MHZ       0xA  // MODE=10, CNF=10
#define GPIO_MODE_AF_OD_2MHZ       0xE  // MODE=10, CNF=11


void InitGPIO(GPIO_TypeDef *PORT, char BROCHE, char CONFIG);
char LireBroche(GPIO_TypeDef *PORT, char BROCHE);
void SetBroche(GPIO_TypeDef *PORT, char BROCHE);
void ResetBroche(GPIO_TypeDef *PORT, char BROCHE);

#endif