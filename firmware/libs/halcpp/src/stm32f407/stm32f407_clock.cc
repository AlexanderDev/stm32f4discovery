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
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE; //PLL source is hse
    RCC->CR |= RCC_CR_PLLON;        // PLL enable
    while(!(RCC->CR & RCC_CR_PLLRDY))
        ;
    FLASH->ACR |= FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN; //prefetch, data/code cache enable
    FLASH->ACR |= FLASH_ACR_LATENCY_5WS; // 5 wait states
    RCC->CFGR |= RCC_CFGR_SW_PLL; //PLL is system clock source
    while(!(RCC->CFGR & RCC_CFGR_SWS_PLL))
        ;
}

template<uint8_t timer_number>
void TIMER<timer_number>::setup(uint32_t freq) {

}

inline uint32_t get_tim_bus_adress(uint8_t timer_number){
    if(timer_number == 1 || (timer_number >= 8 && timer_number <= 11))
        return APB2PERIPH_BASE;
    else if((timer_number >= 2 && timer_number <= 7) || (timer_number >= 12 && timer_number <= 14))
        return APB1PERIPH_BASE;
}

inline TIM_TypeDef *get_tim_regs_adress(uint8_t timer_number){
    uint32_t r, bus_adress = get_tim_bus_adress(timer_number);
    if(timer_number == 1 || timer_number == 8)
        r = (timer_number/8 * 0x0400);
    else if(timer_number >= 2 && timer_number <= 7)
        r = (0x400*(timer_number-2));
    else if(timer_number >= 9 && timer_number <= 11)
        r = (0x4000 + 0x400*(timer_number-9));
    else if(timer_number >= 12 && timer_number <= 14)
        r = (0x1800 + 0x400*(timer_number-12));

    return (TIM_TypeDef *)(bus_adress + r);
}

template<uint8_t timer_number>
void TIMER<timer_number>::init(uint32_t freq) {


    TIM_TypeDef *TIMx = get_tim_regs_adress(timer_number);

    //TIMx->CR2 =| TIM_CR1_CEN;
}

template void TIMER<1>::init(uint32_t);
