#include "halcpp_gpio.hh"
#include "halcpp_clock.hh"

#define CPU_FCLOCK 168000000L // 168 Mhz
#define EXT_FCLOCK   8000000L


void delay(volatile unsigned int nCount) {
    while(nCount--);
}

int main() {
    CLOCK::init(CPU_FCLOCK, EXT_FCLOCK);
    GPIO<D>::init(OUTPUT, 15);
    while(1){
        GPIO<D>::write(15, 1);
        delay(0x40000);
        GPIO<D>::write(15, 0);
        delay(0x40000);
    }
}
