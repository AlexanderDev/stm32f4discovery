/* Includes ------------------------------------------------------------------*/
#include "contiki.h"
#include "net/netstack.h"

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void) {

    process_init();
    //autostart_start(autostart_processes);

    int r=0;
    while (1) {
        do {
            r = process_run();
        } while(r > 0);
        //main_process_poll();
    }
}




