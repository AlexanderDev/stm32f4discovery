#include "led.h"
#include "stm32f4xx.h"

void led_init() {
    GPIO_InitTypeDef        GPIO_InitStructure;
    /* GPIOD Periph clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void led_turn_off() {
    GPIOD->BSRRH = LED_PIN;
}

void led_turn_on() {
    GPIOD->BSRRL = LED_PIN;
}
