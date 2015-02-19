#include "clock.h"
#include "stm32f4xx.h"

/**
    @brief  Initializes microcontroller clock output(MSO) --- PA8 pin
    @param  rcc_mco_source: Clock source for MCO
    @param  rcc_mco_div: Frequency divisor
    @retval None
*/
void init_mco(void){
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    /* Output the system clock on MCO pin (PA.8) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /* System clock selected to output on MCO pin (PA.8)*/
    RCC_MCO1Config(RCC_MCO1Source_HSE, RCC_MCO1Div_1);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    /* Output the system clock on MCO pin (PA.8) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    /* System clock selected to output on MCO pin (PC.9)*/
    RCC_MCO2Config(RCC_MCO2Source_SYSCLK, RCC_MCO2Div_1);
}

void hse_init(uint32_t mul_freq, uint8_t div_freq, uint8_t div_sysclk){
    RCC_HSEConfig(RCC_HSE_ON);                                             //Turn on HSE
    while(RCC_GetFlagStatus(RCC_FLAG_HSERDY)==RESET)                //Is HSE stable?
        ;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    PWR_MainRegulatorModeConfig(PWR_Regulator_Voltage_Scale1);

    RCC_HCLKConfig(RCC_SYSCLK_Div1);                                 //AHB(HCLK) clock
    RCC_PCLK1Config(RCC_HCLK_Div2);                                 //APB1 clock
    RCC_PCLK2Config(RCC_HCLK_Div4);                                 //APB2 clock

    RCC_PLLConfig(RCC_PLLSource_HSE, 
            div_freq, mul_freq, div_sysclk, 7);                     //Set PLL freq. 32Mhz, HSE is source for PLL                                                             // 4 - division factor for OTG FS, SDIO
    RCC_PLLCmd(ENABLE);                                             //Turn on PLL
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET)                //Is PLL stable?
        ;
    FLASH_PrefetchBufferCmd(ENABLE);                                //Turn on prefetch buffer
    FLASH_InstructionCacheCmd(ENABLE);    
    FLASH_DataCacheCmd(ENABLE); 
    FLASH_SetLatency(FLASH_Latency_2);

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);                      //Set system clock source. It is PLL
    while(RCC_GetSYSCLKSource()!=0x08) //PLL
        ;
}

/**
    @brief  Initializes timer for upcounting mode
    @param  TIMx: TIM1, TIM2, TIM3
    @retval Period: value of TIMx_CNT register
    @note   Need enable clock and timer
*/
// uint16_t timer_init(TIM_TypeDef* timx, uint32_t us){
//     uint16_t period=0,prscl=0;
//     uint32_t tics = GET_TICS(us);
//     /*  Calc prescaler:
//         conversion 32 bit prescaler for two 16 bit registers*/
//     if(tics>0xFFFF){
//         prscl=0xFFFF;
//         period=(tics/0xFFFF);
//     }else{
//         period=tics;
//     }
//     TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//     TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//     TIM_TimeBaseStructure.TIM_Period = period;
//     TIM_TimeBaseStructure.TIM_Prescaler = prscl;
//     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//     TIM_TimeBaseInit(timx, &TIM_TimeBaseStructure);
//     return period;
// }

