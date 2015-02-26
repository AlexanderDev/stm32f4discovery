#include "halcpp_interrupt.hh"


void InitIRQChannel(uint8_t NVIC_IRQChannel){
    NVIC_EnableIRQ((IRQn_Type)NVIC_IRQChannel);
}
