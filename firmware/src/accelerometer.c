#include "contiki.h"

#include "hardware.h"

#define BLINK_PAUSE 0x30000 //65536 tick

/*---------------------------------------------------------------------------*/
PROCESS(main_process, "Main process");
AUTOSTART_PROCESSES(&main_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(main_process, ev, data)
{
  PROCESS_BEGIN();
   while(1){
     led_turn_off();
     delay(BLINK_PAUSE);
     led_turn_on();
     delay(BLINK_PAUSE);
   }
  PROCESS_END();
}

void
main_process_poll(void)
{
  process_poll(&main_process);
}

/*---------------------------------------------------------------------------*/
