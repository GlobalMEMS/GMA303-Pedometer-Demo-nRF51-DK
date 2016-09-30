PROJECT_NAME := nRF51_GMA303_Pedo
OUTPUT_FILENAME := nrf51422_xxac

#
# Linker script file
#
LINKER_SCRIPT=.\nRF51_blank.ld

#
# Project source files
#
C_SOURCE_FILES += \
	$(nRF51_SDK_ROOT)/components/drivers_nrf/common/nrf_drv_common.c \
	$(nRF51_SDK_ROOT)/components/drivers_nrf/clock/nrf_drv_clock.c \
	$(nRF51_SDK_ROOT)/components/drivers_nrf/delay/nrf_delay.c \
	$(nRF51_SDK_ROOT)/components/drivers_nrf/gpiote/nrf_drv_gpiote.c \
	$(nRF51_SDK_ROOT)/components/drivers_nrf/rtc/nrf_drv_rtc.c \
	$(nRF51_SDK_ROOT)/components/drivers_nrf/timer/nrf_drv_timer.c \
	$(nRF51_SDK_ROOT)/components/drivers_nrf/twi_master/nrf_drv_twi.c \
	$(nRF51_SDK_ROOT)/components/drivers_nrf/uart/nrf_drv_uart.c \
	$(nRF51_SDK_ROOT)/components/drivers_nrf/nrf_soc_nosd/nrf_soc.c \
	$(nRF51_SDK_ROOT)/components/libraries/button/app_button.c \
	$(nRF51_SDK_ROOT)/components/libraries/fifo/app_fifo.c \
	$(nRF51_SDK_ROOT)/components/libraries/timer/app_timer.c \
	$(nRF51_SDK_ROOT)/components/libraries/twi/app_twi.c \
	$(nRF51_SDK_ROOT)/components/libraries/uart/app_uart_fifo.c \
	$(nRF51_SDK_ROOT)/components/libraries/uart/retarget.c \
	$(nRF51_SDK_ROOT)/components/libraries/util/app_error.c \
	$(nRF51_SDK_ROOT)/components/libraries/util/app_util_platform.c \
	$(nRF51_SDK_ROOT)/components/libraries/util/nrf_assert.c \
	$(nRF51_SDK_ROOT)/components/toolchain/system_nrf51.c \
	$(nRF51_SDK_ROOT)/examples/bsp/bsp.c \
	./m_app_twi.c \
	./bus_support.c \
	./gma303.c \
	./gSensor_autoNil.c \
	./stepCounter_struct_init.c \
	./walkAlg3.c \
	./main.c

#
# Project include path
#
INC_PATHS  = -I. 

#
# For verbose output, set
# VERBOSE = 1
#
VERBOSE := 0

#
# To turn on all warning and treat it as error, set to 1
#
STRICT_WARNING_IS_ERROR := 0

#
#
# The utility functions
#
#
MK := mkdir
RM := rm -rf

#
# The base directory for nRF51 SDK
#
nRF51_SDK_ROOT := /C/Data/nRF51_SDK/V10_0_0

MAKEFILE_NAME := $(MAKEFILE_LIST)
MAKEFILE_DIR := $(dir $(MAKEFILE_NAME) )
TEMPLATE_PATH = $(nRF51_SDK_ROOT)/components/toolchain/gcc

ifeq ($(OS),Windows_NT)
include $(TEMPLATE_PATH)/Makefile.windows
else
include $(TEMPLATE_PATH)/Makefile.posix
endif

GNU_INSTALL_ROOT := C:/Program Files (x86)/GNU Tools ARM Embedded/4.9 2015q1

#echo suspend
ifeq ("$(VERBOSE)","1")
NO_ECHO := 
else
NO_ECHO := @
endif

# Toolchain commands
CC              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-gcc'
AS              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-as'
AR              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ar' -r
LD              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ld'
NM              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-nm'
OBJDUMP         := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objdump'
OBJCOPY         := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objcopy'
SIZE            := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-size'

#function for removing duplicates in a list
remduplicates = $(strip $(if $1,$(firstword $1) $(call remduplicates,$(filter-out $(firstword $1),$1))))

#assembly files common to all targets
ASM_SOURCE_FILES  = $(abspath $(nRF51_SDK_ROOT)/components/toolchain/gcc/gcc_startup_nrf51.s)

#includes common to all targets
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/device
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/drivers_nrf/clock
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/drivers_nrf/common
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/drivers_nrf/config
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/drivers_nrf/delay
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/drivers_nrf/gpiote
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/drivers_nrf/hal
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/drivers_nrf/nrf_soc_nosd
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/drivers_nrf/rtc
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/drivers_nrf/timer
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/drivers_nrf/twi_master
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/drivers_nrf/uart
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/libraries/button
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/libraries/fifo
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/libraries/uart
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/libraries/util
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/libraries/timer
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/libraries/twi
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/toolchain
INC_PATHS += -I$(nRF51_SDK_ROOT)/components/toolchain/gcc
INC_PATHS += -I$(nRF51_SDK_ROOT)/examples/bsp

OBJECT_DIRECTORY = _build
LISTING_DIRECTORY = $(OBJECT_DIRECTORY)
OUTPUT_BINARY_DIRECTORY = $(OBJECT_DIRECTORY)

# Sorting removes duplicates
BUILD_DIRECTORIES := $(sort $(OBJECT_DIRECTORY) $(OUTPUT_BINARY_DIRECTORY) $(LISTING_DIRECTORY) )

#flags common to all targets
CFLAGS  = -DNRF51
CFLAGS += -DSWI_DISABLE0
CFLAGS += -DBOARD_PCA10028
##CFLAGS += -DBSP_DEFINES_ONLY ##define BSP_DEFINES_ONLY will reduce buttons functionality
CFLAGS += -mcpu=cortex-m0
CFLAGS += -mthumb -mabi=aapcs --std=gnu99

ifeq ("$(STRICT_WARNING_IS_ERROR)","1")
CFLAGS += -Wall -Werror -O3
else
CFLAGS += -O3
endif

CFLAGS += -mfloat-abi=soft
# keep every function in separate section. This will allow linker to dump unused functions
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin --short-enums

# keep every function in separate section. This will allow linker to dump unused functions
LDFLAGS += -Xlinker -Map=$(LISTING_DIRECTORY)/$(OUTPUT_FILENAME).map
LDFLAGS += -mthumb -mabi=aapcs -L $(TEMPLATE_PATH) -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m0
# let linker to dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs -lc -lnosys
# use math.h
LIBS += -lm

# Assembler flags
ASMFLAGS += -x assembler-with-cpp
ASMFLAGS += -DNRF51
ASMFLAGS += -DBOARD_PCA10028
ASMFLAGS += -DBSP_DEFINES_ONLY
#default target - first one defined
default: nrf51422_xxac

#building all targets
all: nrf51422_xxac flash_blank

#target for printing all targets
help:
	@echo following targets are available:
	@echo   all
	@echo 	nrf51422_xxac
	@echo   flash_blank
	@echo   clean


C_SOURCE_FILE_NAMES = $(notdir $(C_SOURCE_FILES))
C_PATHS = $(call remduplicates, $(dir $(C_SOURCE_FILES) ) )
C_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(C_SOURCE_FILE_NAMES:.c=.o) )

ASM_SOURCE_FILE_NAMES = $(notdir $(ASM_SOURCE_FILES))
ASM_PATHS = $(call remduplicates, $(dir $(ASM_SOURCE_FILES) ))
ASM_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(ASM_SOURCE_FILE_NAMES:.s=.o) )

vpath %.c $(C_PATHS)
vpath %.s $(ASM_PATHS)

OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

nrf51422_xxac: $(BUILD_DIRECTORIES) $(OBJECTS) 
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(NO_ECHO)$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e finalize

## Create build directories
$(BUILD_DIRECTORIES):
	@echo $(MAKEFILE_NAME): building directory $@
	$(NO_ECHO)$(MK) $@

# Create objects from C SRC files
$(OBJECT_DIRECTORY)/%.o: %.c
	@echo Compiling file: $(notdir $<)
	$(NO_ECHO)$(CC) $(CFLAGS) $(INC_PATHS) -c -o $@ $<

# Assemble files
$(OBJECT_DIRECTORY)/%.o: %.s
	@echo Compiling file: $(notdir $<)
	$(NO_ECHO)$(CC) $(ASMFLAGS) $(INC_PATHS) -c -o $@ $<


# Link
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out: $(BUILD_DIRECTORIES) $(OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(NO_ECHO)$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out


## Create binary .bin file from the .out file
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).bin
	$(NO_ECHO)$(OBJCOPY) -O binary $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin

## Create binary .hex file from the .out file
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).hex
	$(NO_ECHO)$(OBJCOPY) -O ihex $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex

#
#
#
.PHONY: finalize genbin genhex echosize clean cleanobj flash_blank
finalize: genbin genhex echosize

genbin:
	@echo Preparing: $(OUTPUT_FILENAME).bin
	$(NO_ECHO)$(OBJCOPY) -O binary $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin

## Create binary .hex file from the .out file
genhex: 
	@echo Preparing: $(OUTPUT_FILENAME).hex
	$(NO_ECHO)$(OBJCOPY) -O ihex $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex

echosize:
	-@echo ''
	$(NO_ECHO)$(SIZE) $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	-@echo ''

clean:
	@echo Removing directory $(BUILD_DIRECTORIES)
	$(NO_ECHO)$(RM) $(BUILD_DIRECTORIES)

cleanobj:
	@echo Removing objs
	$(NO_ECHO)$(RM) $(BUILD_DIRECTORIES)/*.o

flash_blank:
	@echo Blank Flashing: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex
	$(NO_ECHO)nrfjprog --program $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex -f nrf51  --chiperase
	$(NO_ECHO)nrfjprog --reset

flash_app:
	@echo Application Flashing: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex
	$(NO_ECHO)nrfjprog --program $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex -f nrf51  --sectorerase
	$(NO_ECHO)nrfjprog --reset

## Flash softdevice
flash_softdevice:
	@echo Flashing: s110_nrf51_8.0.0_softdevice.hex
	nrfjprog --program $(nRF51_SDK_ROOT)/components/softdevice/s110/hex/s110_nrf51_8.0.0_softdevice.hex -f nrf51 --chiperase
	nrfjprog --reset
