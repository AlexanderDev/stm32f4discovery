### Import virable:	TOOLCHAIN
###

### Toolchain definition.
CROSS_COMPILE:=arm-none-eabi

OBJCOPY= $(CROSS_COMPILE)-objcopy
OBJDUMP= $(CROSS_COMPILE)-size
NM = $(CROSS_COMPILE)-nm

CXX= $(CROSS_COMPILE)-g++
CC= $(CROSS_COMPILE)-gcc
AR = $(CROSS_COMPILE)-ar
LD = $(CROSS_COMPILE)-ld
OBJDUMP = $(CROSS_COMPILE)-objdump
SIZE = $(CROSS_COMPILE)-size


# should use --gc-sections but the debugger does not seem to be able to cope with the option.
LINKER_FLAGS=	-Wl,--gc-sections -mcpu=cortex-m3 -mthumb -msoft-float

# Debugging format.
DEBUG=   -ggdb

# Optimization level, can be [0, 1, 2, 3, s].
OPT = 0

# Compiler flags definition.
CFLAGS+= -Wattributes \
		$(DEBUG) \
		-O$(OPT) \
		-mcpu=cortex-m3 -mthumb -msoft-float\
		-fno-builtin \
		-Wall \
		-fdata-sections \
		-ffunction-sections \
		-D STM32F40_41xxx

CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -std=c++11

OBJOPTS = -O binary

ifeq ($(V),1)
  override TRACE_CC =
  override TRACE_LD =
  override TRACE_AR =
  override TRACE_AS =
  override TRACE_CXX =
  override Q=
else
  override TRACE_CC = @echo "  CC       " $(notdir $<)
  override TRACE_LD = @echo "  LD       " $(notdir $@)
  override TRACE_AR = @echo "  AR       " $(notdir $@)
  override TRACE_AS = @echo "  AS       " $(notdir $<)
  override TRACE_CXX = @echo "  CXX      " $(notdir $<)
  override Q=@
endif











