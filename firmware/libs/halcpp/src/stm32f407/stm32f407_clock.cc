#include "stm32f4xx.h"
#include "halcpp_clock.hh"
#include "halcpp_interrupt.hh"
#include "halcpp_gpio.hh"

#define AHB_PRESC 1 //PLL CLOCK
#define APB1_PRESC 4 //42 Mhz
#define APB2_PRESC 2 //84 Mhz

extern "C" {
    void TIM1_UP_TIM10_IRQHandler(void);
    void TIM2_IRQHandler(void);
}

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

/*
    Timers
*/
TIM_TypeDef *tim_adress[]= {TIM1, TIM2, TIM3, TIM4, TIM5, TIM6, TIM7,
                            TIM8, TIM9, TIM10, TIM11, TIM12, TIM13, TIM14
                           };

uint16_t tim_apb_bus=0b11110000001; //bit map there is position - tim number, (0/1) -> (apb1/apb2)
uint8_t tim_rcc_bit[]= {0, 0, 1, 2, 3, 4, 5, 1, 16, 17, 18, 6, 7, 8};

TIM_TypeDef *tim_x(uint8_t x) {
    return tim_adress[x-1];
}

template<uint8_t timer_number>
void TIMER<timer_number>::init(uint32_t freq) {
    if(tim_apb_bus&(1<<(timer_number-1)))
        RCC->APB2ENR |= (1 << tim_rcc_bit[timer_number-1]);
    else
        RCC->APB1ENR |= (1 << tim_rcc_bit[timer_number-1]);
    TIMER<timer_number>::setup(freq);
}

template<uint8_t timer_number>
void TIMER<timer_number>::setup(uint32_t freq) {
    TIM_TypeDef *TIMx = tim_x(timer_number);
    uint32_t psc=CPU_FCLOCK/freq;
    if(freq<=CPU_FCLOCK) {
        TIMx->ARR=psc&0xFFFF;
        TIMx->PSC=(psc>>16);
    }
    TIMx->CR1 |= TIM_CR1_CEN;
}

enum IRQ_TIMER {
    IRQ_TIM1=TIM1_UP_TIM10_IRQn,
    IRQ_TIM2=TIM2_IRQn
};

uint8_t timx_interr[]={IRQ_TIM1, IRQ_TIM2};

template<uint8_t timer_number>
void TIMER<timer_number>::interrupt(uint8_t src) {
    TIM_TypeDef *TIMx = tim_x(timer_number);
    TIMx->DIER |= TIM_IT_Update; // source interrupt
    InitIRQChannel(timx_interr[timer_number-1]);
}

void TIM1_UP_TIM10_IRQHandler(void) {
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
        static uint8_t t=0;
        GPIO<D>::write(13, (t ? t-- : t++));
    }
}


template void TIMER<1>::init(uint32_t);
template void TIMER<1>::setup(uint32_t);
template void TIMER<1>::interrupt(uint8_t);

template void TIMER<2>::init(uint32_t);
template void TIMER<2>::setup(uint32_t);
template void TIMER<2>::interrupt(uint8_t);
