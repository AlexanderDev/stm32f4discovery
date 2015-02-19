#include <stm32f407_gpio.hh>
#include <halcpp_gpio.hh>

inline GPIO_TypeDef *get_adress_gpio_regs(uint8_t port_number){
    return ((GPIO_TypeDef *) (AHB1PERIPH_BASE + 0x0400 * port_number));
}


template<uint8_t port_number>
void GPIO<port_number>::write(uint8_t pin, uint8_t value) {
    GPIO_TypeDef *GPIOx=get_adress_gpio_regs(port_number);
    if(value)
        GPIOx->BSRRL |= 0x1 << pin;
    else
        GPIOx->BSRRH |= 0x1 << pin;
}

template<uint8_t port_number>
void GPIO<port_number>::init(uint32_t flags, int8_t pin=-1) {
    GPIO_TypeDef *GPIOx=get_adress_gpio_regs(port_number);
    /* GPIO Periph clock enable */
    RCC->AHB1ENR |= 0x1 << port_number;

    if(pin==-1)
        return;

    if(flags & INPUT){
        GPIOx->MODER&=~(0b11 << (pin*2));
    }else{
        GPIOx->MODER|=(0b01 << (pin*2));
    }
}

template void GPIO<A>::init(uint32_t, int8_t);
template void GPIO<B>::init(uint32_t, int8_t);
template void GPIO<C>::init(uint32_t, int8_t);
template void GPIO<D>::init(uint32_t, int8_t);

template void GPIO<A>::write(uint8_t, uint8_t);
template void GPIO<B>::write(uint8_t, uint8_t);
template void GPIO<C>::write(uint8_t, uint8_t);
template void GPIO<D>::write(uint8_t, uint8_t);
