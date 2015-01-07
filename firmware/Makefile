#CONTIKI_PROJECT = accelerometer
CONTIKI_PROJECT = blink
CPU_LABEL = stm32f407
TARGET=stm32f4discovery

PROJECTDIRS += src src/inc

#PROJECT_SOURCEFILES += 

all: $(CONTIKI_PROJECT)

### Build libs
LIBPATH=$(CURDIR)/libs
CONTIKI =  $(LIBPATH)/contiki
include $(CONTIKI)/Makefile.include

