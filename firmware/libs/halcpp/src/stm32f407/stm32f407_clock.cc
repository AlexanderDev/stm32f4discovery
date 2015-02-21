#include "stm32f4xx.h"
#include "halcpp_clock.hh"

#define AHB_PRESC 1 //PLL CLOCK
#define APB1_PRESC 4 //42 Mhz
#define APB2_PRESC 2 //84 Mhz

constexpr uint32_t pll_config(uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ) {
    return PLLM | (PLLN << 6) | (((PLLP >> 1) -1) << 16) | (PLLQ << 24);
}

void CLOCK::init(uint32_t clock, uint32_t ext_clock) {
    RCC->CR |= RCC_CR_HSEON; // HSE enable
    while(!(RCC->CR & RCC_CR_HSERDY))
        ;
    RCC->PLLCFGR = pll_config(5, 210, 2, 8); // FPLL = 168Mhz FUSB=42Mhz FEXT=8Mgz
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
    RCC->CR |= RCC_CR_PLLON; // HSE enable
    while(!(RCC->CR & RCC_CR_PLLRDY))
        ;
    FLASH->ACR |= FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN;
    FLASH->ACR |= FLASH_ACR_LATENCY_5WS;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while(!(RCC->CFGR & RCC_CFGR_SWS_PLL))
        ;
}
