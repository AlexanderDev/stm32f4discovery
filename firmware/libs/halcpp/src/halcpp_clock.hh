#ifndef HALCPP_CLOCK_HH_INCLUDED
#define HALCPP_CLOCK_HH_INCLUDED

#include <stm32f4xx.h>


class CLOCK {
public:
    static void init(uint32_t clock, uint32_t ext_clock=0);
};

#endif // HALCPP_CLOCK_HH_INCLUDED
