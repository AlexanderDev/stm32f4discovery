#ifndef HALCPP_CLOCK_HH_INCLUDED
#define HALCPP_CLOCK_HH_INCLUDED

#include <stm32f4xx.h>


class CLOCK {
public:
    static void init(uint32_t clock, uint32_t ext_clock=0);
};

template<uint8_t>
class TIMER {
public:
    static void init(uint32_t freq);
    static void setup(uint32_t freq);
    static void interrupt(uint8_t src=0);
};

#define CPU_FCLOCK 168000000L // 168 Mhz
#define EXT_FCLOCK   8000000L


#endif // HALCPP_CLOCK_HH_INCLUDED
