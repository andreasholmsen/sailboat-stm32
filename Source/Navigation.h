#ifndef __NAVIGATION_H
#define __NAVIGATION_H

#include "stm32f10x.h"
#include "GPIO.h"
#include "UART.h"
#include "timer.h"
#include "PWM.h"
#include "interuption.h"
#include "math.h"

void InitNavigation(void);
void UpdateNavigation(void);

#endif