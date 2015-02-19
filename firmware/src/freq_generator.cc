#include "halcpp_gpio.hh"


#define LED_PIN GPIO_Pin_15


void delay(volatile unsigned int nCount) {
    while(nCount--);
}

int main() {
    GPIO<D>::init(OUTPUT, 15);
    while(1){
        GPIO<D>::write(15, 1);
        delay(0x40000);
        GPIO<D>::write(15, 0);
        delay(0x40000);
    }
}
