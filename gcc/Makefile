SOURCE_DIRS:= device/source ../source ../retarget/source ../mdk/RTE/CMSIS
INCLUDE_DIRS:= device/include cmsis/include ../include ../retarget/include ./CMSIS_RTX/include ../mdk/RTE
LINKER_DIRS:= ./CMSIS_RTX/bin/

OUTPUT_EXEC:= salida.elf

#All the dtandard peripherial library files
SPL_FILES:= $(notdir $(wildcard ../STM32F30x_StdPeriph_Driver/src/*.c ))

C_SOURCE_FILES:= system_TM4C123.c RTX_Conf_CM.c delay.c
CXX_SOURCE_FILES:= main.cc serial_stream.cc serial_stream_tm4c.cc RGBLed.cc I2CBus_TM4C.cc MPU6050.cc
ASM_SOURCE_FILES:= startup_ARMCM4.S
LINKER_FILES:= ./CMSIS_RTX/bin/libRTX_CM4.a

LD_SCRIPTS:= gcc_arm.ld

C_OBJECTS:= $(C_SOURCE_FILES:.c=.o)
CXX_OBJECTS:= $(CXX_SOURCE_FILES:.cc=.o)
ASM_OBJECTS:= $(ASM_SOURCE_FILES:.S=.o)

TARGET_CHIP:= TM4C123GH6PM
ARCH_FLAGS:= -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
COMMON_FLAGS:= -Wall -g -ffunction-sections -fdata-sections -fno-exceptions
USER_CPP_FLAGS:=
USER_DEFINES:= USE_STDPERIPH_DRIVER
USER_ASM_FLAGS:= -std=c99
USER_C_FLAGS:= -std=c99
USER_CXX_FLAGS:= -std=c++11 -flto -O0
USER_LINKER_FLAGS:= -std=c++11 -Wl,--gc-sections -specs=nano.specs --specs=nosys.specs -u _printf_float -flto -O0

CPP_DEFINES:= $(TARGET_CHIP) $(USER_DEFINES)
CPP_DEFINE_FLAGS:=$(patsubst %,-D%,$(CPP_DEFINES))
INCLUDE_FLAGS:= $(patsubst %,-I%,$(INCLUDE_DIRS))
CPP_FLAGS:= $(CPP_DEFINE_FLAGS) $(INCLUDE_FLAGS) $(USER_CPP_FLAGS)

#LINKER OPTIONS
#The linker script for the microcontroller
LD_SCRIPTS:= gcc_arm.ld
#the directories for linker files
LIB_DIRS:= device/
#the libraries to link
LIB_NAMES:=
#linker flags
LFLAGS:= $(patsubst %,-L%,$(LIB_DIRS)) $(patsubst %,-l%,$(LIB_NAMES)) -T$(LD_SCRIPTS)

ASM_FLAGS:= $(ARCH_FLAGS) $(COMMON_FLAGS) $(USER_ASM_FLAGS)
C_FLAGS:= $(ARCH_FLAGS) $(COMMON_FLAGS) $(USER_C_FLAGS)
CXX_FLAGS:= $(ARCH_FLAGS) $(COMMON_FLAGS) $(USER_CXX_FLAGS)
LINKER_FLAGS:= $(ARCH_FLAGS) $(COMMON_FLAGS) $(USER_LINKER_FLAGS) $(patsubst %,-L%,$(LIB_DIRS)) $(patsubst %,-l%,$(LIB_NAMES)) -T$(LD_SCRIPTS)

OBJECTS_DIR:= objects
BIN_DIR:= bin

DIRS_TO_CREATE:= $(OBJECTS_DIR) $(BIN_DIR)

OBJECTS:= $(C_OBJECTS) $(CXX_OBJECTS) $(ASM_OBJECTS)
OBJECTS_WITH_PATH:= $(patsubst %,$(OBJECTS_DIR)/%,$(OBJECTS))

CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++
AS=arm-none-eabi-gcc
LN=arm-none-eabi-g++

vpath %.c $(SOURCE_DIRS)
vpath %.cc $(SOURCE_DIRS)
vpath %.S $(SOURCE_DIRS)
vpath %.o $(OBJECTS_DIR)
vpath %.a $(BIN_DIR) $(LINKER_DIRS)
vpath %.elf $(BIN_DIR)

.PHONY: disp clean debug burn

all: $(OUTPUT_EXEC)
$(OUTPUT_EXEC): $(OBJECTS) $(LINKER_FILES)
	$(LN) $(OBJECTS_WITH_PATH) $(LINKER_FILES) $(LINKER_FLAGS) -o $@
	arm-none-eabi-size $@
$(DIRS_TO_CREATE): %:
	mkdir $@
$(C_OBJECTS): %.o : %.c | $(OBJECTS_DIR)
	$(CC) -c $(C_FLAGS) $(CPP_FLAGS) $< -o $(OBJECTS_DIR)/$@
$(ASM_OBJECTS): %.o : %.S | $(OBJECTS_DIR)
	$(AS) -c $(ASM_FLAGS) $(CPP_FLAGS) $< -o $(OBJECTS_DIR)/$@
$(CXX_OBJECTS): %.o : %.cc | $(OBJECTS_DIR)
	$(CXX) -c $(CXX_FLAGS) $(CPP_FLAGS) $< -o $(OBJECTS_DIR)/$@
clean:
	rm -rf $(DIRS_TO_CREATE) $(OUTPUT_EXEC)
dist_clean: clean

burn: salida.elf
	/usr/bin/openocd -fboard/ek-tm4c123gxl.cfg -c"init" -c"reset" -c"sleep 300" -c"reset halt" -c"sleep 300" -c"flash write_image erase salida.elf 0x00 elf" -c"reset" -c"shutdown";
debug: salida.elf
	/usr/bin/openocd -fboard/ek-tm4c123gxl.cfg &> /dev/null &
	sleep 1 ;
	! echo "reset" | telnet localhost 4444 &> /dev/null ;
	! echo "reset halt" | telnet localhost 4444 &> /dev/null ;
	sleep 0.5 ;
	arm-none-eabi-gdb --tui --eval-command="target remote localhost:3333" salida.elf ;
	! echo "reset" | telnet localhost 4444 &> /dev/null;
	sleep 0.5 ;
	! echo "shutdown" | telnet localhost 4444 &> /dev/null;
	sleep 0.1 ;
