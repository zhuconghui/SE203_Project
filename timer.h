#ifndef TIMER_H
#define TIMER_H

#include "CMSIS/stm32l475xx.h"
#include "led.h"
#include "matrix.h"

void timer_init(int max_us);

#endif // TIMER_H
