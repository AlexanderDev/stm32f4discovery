#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

#define LED_PIN GPIO_Pin_13

extern void led_init();
extern void led_turn_off();
extern void led_turn_on();

#endif // LED_H_INCLUDED
