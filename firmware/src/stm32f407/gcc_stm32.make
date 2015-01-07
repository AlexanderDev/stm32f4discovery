### Import virable:	TOOLCHAIN
###

### Toolchain definition.
CROSS_COMPILE:=$(TOOLCHAIN)/bin/arm-none-eabi

OBJCOPY= $(CROSS_COMPILE)-objcopy
OBJDUMP= $(CROSS_COMPILE)-size
NM = $(CROSS_COMPILE)-nm

CC=$(CROSS_COMPILE)-gcc
AR = $(CROSS_COMPILE)-ar
LD = $(CROSS_COMPILE)-ld


TOOLCHAIN_INC_DIR=$(TOOLCHAIN)/arm-none-eabi/include
TOOLCHAIN_LIB_DIR=$(TOOLCHAIN)/arm-none-eabi/lib


# should use --gc-sections but the debugger does not seem to be able to cope with the option.
LINKER_FLAGS=	-nostartfiles -Wl,--gc-sections -mthumb -mcpu=cortex-m3

# Debugging format.
DEBUG= gdb

# Optimization level, can be [0, 1, 2, 3, s].
OPT = 0

# Compiler flags definition.
CFLAGS+= -Wattributes \
		-g$(DEBUG) \
		-O$(OPT) \
		-isystem $(TOOLCHAIN_INC_DIR) \
		-mcpu=cortex-m3 -mthumb \
		-fno-builtin \
		-Wall \
		-std=gnu99 \
		-fdata-sections \
		-ffunction-sections \

OBJOPTS = -O binary















