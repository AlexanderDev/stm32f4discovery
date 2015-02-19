#ifndef CLOCK_H_INCLUDED
#define CLOCK_H_INCLUDED

#include "stm32f4xx.h"


#define CPU_CLOCK 64000000 // Hz

// Time in usecond
#define GET_TICS(usec) ((usec) * (CPU_CLOCK/1000000))

// Conver Hertz to usecond
#define HZ_TO_US(hz) (1000000/(hz))

/**
    @brief  Initializes microcontroller clock output(MSO) --- PA8 pin
    @param  rcc_mco_source: Clock source for MCO
    @param  rcc_mco_div: Frequency divisor
    @retval None
*/
void init_mco(void);

/**
    @brief  Initializes HSE for system clock through PLL
    @param  div_freq: Divisor of HSI frequency(16 Mhz)
    @param  mul_freq: Multiplier of HSI frequency(16 Mhz)
    @param  div_sysclk: Divisor for SYSCLOCK frequency
    @retval None
*/
void hse_init(uint32_t mul_freq, uint8_t div_freq, uint8_t div_sysclk);

/**
    @brief  Initializes timer for upcounting mode
    @param  TIMx: TIM1, TIM2, TIM3
    @retval Period: value of TIMx_CNT register
    @note   Need enable clock and timer
*/
uint16_t timer_init(TIM_TypeDef* timx, uint32_t us);
#endif // CLOCK_H_INCLUDED
