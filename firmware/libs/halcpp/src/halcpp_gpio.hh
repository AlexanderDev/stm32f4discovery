#ifndef HALCPP_GPIO_HH_INCLUDED
#define HALCPP_GPIO_HH_INCLUDED

#include <stm32f4xx.h>

enum GPIO_NUM { A=0, B=1, C=2, D=3, E=4 };
enum GPIO_MODE { INPUT=0, OUTPUT=2 };

template<uint8_t>
class GPIO {
public:
    static void write(uint8_t pin, uint8_t value);
    static void init(uint32_t flags, int8_t pin=-1);
};

#endif // HALCPP_GPIO_HH_INCLUDED
