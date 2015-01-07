/* Includes ------------------------------------------------------------------*/
#include "contiki.h"
#include "net/netstack.h"

#include "hardware.h"

void main_process_poll(void);

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void) {

    hw_init();
    process_init();
    autostart_start(autostart_processes);

    while (1) {
        main_process_poll();
        int n = process_run();
    }
}




