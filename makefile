TARGET = main.elf

SRC_DIR = ./src
INC_DIR = ./inc

CMSIS_DIR = ./CMSIS
CORE_SUPPORT_DIR = $(CMSIS_DIR)/CM3/CoreSupport
DEVICE_SUPPORT_DIR = $(CMSIS_DIR)/CM3/DeviceSupport/ST/STM32F10x

MEMORY_MANAGER_DIR = ./memoryManager
MEMORY_MANAGER_SRC = $(MEMORY_MANAGER_DIR)/src
MEMORY_MANAGER_INC = $(MEMORY_MANAGER_DIR)/inc

THREAD_MANAGER_DIR = ./threadManager
THREAD_MANAGER_SRC = $(THREAD_MANAGER_DIR)/src
THREAD_MANAGER_INC = $(THREAD_MANAGER_DIR)/inc

LIST_DIR = ./list
LIST_SRC = $(LIST_DIR)/src
LIST_INC = $(LIST_DIR)/inc

CC = arm-none-eabi-gcc

CCFLAGS = -mcpu=cortex-m3
CCFLAGS += -mthumb
CCFLAGS += -I.
CCFLAGS += -I$(INC_DIR)
CCFLAGS += -I$(CORE_SUPPORT_DIR)
CCFLAGS += -I$(DEVICE_SUPPORT_DIR)
CCFLAGS += -I$(MEMORY_MANAGER_INC)
CCFLAGS += -I$(THREAD_MANAGER_INC)
CCFLAGS += -I$(LIST_INC)
CCFLAGS += --specs=nosys.specs
CCFLAGS += -g

INPUT = main.c
INPUT += $(MEMORY_MANAGER_SRC)/memory.c
INPUT += $(THREAD_MANAGER_SRC)/thread.c
INPUT += $(LIST_SRC)/list.c
INPUT += $(DEVICE_SUPPORT_DIR)/startup/gcc_ride7/startup_stm32f10x_ld.s
INPUT += $(DEVICE_SUPPORT_DIR)/system_stm32f10x.c
INPUT += $(CORE_SUPPORT_DIR)/core_cm3.c
INPUT += $(wildcard $(SRC_DIR)/*.c)

ASM_INPUT = main.c
ASM_INPUT += $(DEVICE_SUPPORT_DIR)/startup/gcc_ride7/startup_stm32f10x_ld.s

LD = -T./linkerScript.ld

OUTPUT = -o $(TARGET)

main:
	$(CC) $(CCFLAGS) $(INPUT) $(LD) $(OUTPUT)

assembly:
	$(CC) $(CCFLAGS) -S $(ASM_INPUT) $(LD)