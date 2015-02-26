#include "halcpp_gpio.hh"
#include "halcpp_clock.hh"


void delay(volatile unsigned int nCount) {
    while(nCount--);
}


int main() {
    CLOCK::init(CPU_FCLOCK, EXT_FCLOCK);
    GPIO<D>::init(OUTPUT, 15);
    GPIO<D>::init(OUTPUT, 13);
    TIMER<1>::init(1);
    TIMER<1>::interrupt();
    while(1) {
        GPIO<D>::write(15, 1);
        delay(0x40000);
        GPIO<D>::write(15, 0);
        delay(0x40000);
    }
}
