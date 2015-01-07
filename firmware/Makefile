CONTIKI_PROJECT = accelerometer
#CONTIKI_PROJECT = blink
CPU_LABEL = stm32f407
TARGET=stm32f4discovery

PROJECTDIRS += src src/inc

#PROJECT_SOURCEFILES += 

all: $(CONTIKI_PROJECT).bin

### Build libs
LIBPATH=$(CURDIR)/libs
CONTIKI =  $(LIBPATH)/contiki
include $(CONTIKI)/Makefile.include

load: $(CONTIKI_PROJECT).bin
	openocd -f board/stm32f4discovery.cfg -c "program $(OBJECTDIR)/$(CONTIKI_PROJECT).elf  verify reset"

openocd:
	openocd -f board/stm32f4discovery.cfg