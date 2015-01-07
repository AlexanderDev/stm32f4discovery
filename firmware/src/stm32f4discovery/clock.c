#include "stm32l1xx.h"
#include "clock.h"
/**
    @brief  Initializes microcontroller clock output(MSO) --- PA8 pin
    @param  rcc_mco_source: Clock source for MCO
    @param  rcc_mco_div: Frequency divisor
    @retval None
*/
void init_mco(uint8_t rcc_mco_source, uint8_t rcc_mco_div){
    GPIO_InitTypeDef  GPIO_InitStructure;
    /* Enable the GPIOC peripheral */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* Output the system clock on MCO pin (PA.8) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* System clock selected to output on MCO pin (PA.8)*/
    RCC_MCOConfig(rcc_mco_source, rcc_mco_div);
}

/**
    @brief  Initializes HSI for system clock through PLL
    @param  div_freq: Divisor of HSI frequency(16 Mhz)
    @param  mul_freq: Multiplier of HSI frequency(16 Mhz)
    @retval None
*/
void hsi_init(uint8_t mul_freq, uint8_t div_freq){
    RCC_HSICmd(ENABLE);	                                            //Turn on HSI
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY)==RESET)                //Is HSI stable?
        ;

    RCC_PLLConfig(RCC_PLLSource_HSI, mul_freq, div_freq);             //Set PLL freq. 32Mhz, HSI is source for PLL
    RCC_PLLCmd(ENABLE);	                                            //Turn on PLL
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET)                //Is PLL stable?
        ;

    FLASH_ReadAccess64Cmd(ENABLE);                                  //Cpu read two words
    FLASH_SetLatency(FLASH_Latency_1);                              //Set two cpu wait cycle
    FLASH_PrefetchBufferCmd(ENABLE);                                //Turn on prefetch buffer
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);                      //Set system clock source. It is PLL
    RCC_MSICmd(DISABLE);                                            //Turn off MSI                                          //Turn off MSI
}

/**
    @brief  Initializes timer for upcounting mode
    @param  TIMx: TIM1, TIM2, TIM3
    @retval Period: value of TIMx_CNT register
    @note   Need enable clock and timer
*/
uint16_t timer_init(TIM_TypeDef* timx, uint32_t us){
    uint16_t period=0,prscl=0;
    uint32_t tics = GET_TICS(us);
    /*  Calc prescaler:
        conversion 32 bit prescaler for two 16 bit registers*/
    if(tics>0xFFFF){
        prscl=0xFFFF;
        period=(tics/0xFFFF);
    }else{
        period=tics;
    }
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = period;
    TIM_TimeBaseStructure.TIM_Prescaler = prscl;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(timx, &TIM_TimeBaseStructure);
    return period;
}

