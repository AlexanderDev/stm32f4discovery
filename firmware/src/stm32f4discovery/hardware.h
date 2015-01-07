#ifndef HARDWARE_H_INCLUDED
#define HARDWARE_H_INCLUDED

#include <assert.h>

#include "stm32f4xx.h"
#include "led.h"
//#include "clock.h"


#define DEBUG_PIN GPIO_Pin_12

void hw_init(void);
void delay(volatile uint32_t nCount);
void debug_pin_init();
void debug_pin_on();
void debug_pin_off();
void debug_pin_toggle_delay(uint32_t n);

#endif // HARDWARE_H_INCLUDED
