#include "halcpp_gpio.hh"
#include "halcpp_clock.hh"


void delay(volatile unsigned int nCount) {
    while(nCount--);
}

void TIM1_IRQHandler(void) {
    static uint8_t t=0;
    GPIO<D>::write(13, (t ? t-- : t++));
}

int main() {
    CLOCK::init(CPU_FCLOCK, EXT_FCLOCK);
    GPIO<D>::init(OUTPUT, 15);
    GPIO<D>::init(OUTPUT, 13);
    TIMER<1>::init(60);
    while(1) {
        GPIO<D>::write(15, 1);
        delay(0x40000);
        GPIO<D>::write(15, 0);
        delay(0x40000);
    }
}


