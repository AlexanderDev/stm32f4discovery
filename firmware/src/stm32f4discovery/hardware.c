#include "hardware.h"
#include <stdio.h>


void
hw_init(void) {
    //hsi_init(RCC_PLLMul_6, RCC_PLLDiv_4); /*24 Mhz*/
    led_init();
    led_turn_on();
}

void delay(volatile uint32_t nCount) {
    while(nCount--);
}

void debug_pin_init() {
    GPIO_InitTypeDef        GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = DEBUG_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void debug_pin_on() {
    GPIOD->BSRRL = DEBUG_PIN;
}

void debug_pin_off() {
    GPIOD->BSRRH = DEBUG_PIN;
}

void debug_pin_toggle_delay(uint32_t n) {
    GPIO_ToggleBits(GPIOD, DEBUG_PIN);
    delay(n);
}



