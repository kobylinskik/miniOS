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

CC_FLAGS = -mcpu=cortex-m3
CC_FLAGS += -mthumb
CC_FLAGS += -I.
CC_FLAGS += -I$(INC_DIR)
CC_FLAGS += -I$(CORE_SUPPORT_DIR)
CC_FLAGS += -I$(DEVICE_SUPPORT_DIR)
CC_FLAGS += -I$(MEMORY_MANAGER_INC)
CC_FLAGS += -I$(THREAD_MANAGER_INC)
CC_FLAGS += -I$(LIST_INC)
CC_FLAGS += --specs=nosys.specs
CC_FLAGS += -g

INPUT = main.c
INPUT += $(MEMORY_MANAGER_SRC)/memory.c
INPUT += $(wildcard $(THREAD_MANAGER_SRC)/*.c)
INPUT += $(LIST_SRC)/list.c
INPUT += $(DEVICE_SUPPORT_DIR)/startup/gcc_ride7/startup_stm32f10x_ld.s
INPUT += $(DEVICE_SUPPORT_DIR)/system_stm32f10x.c
INPUT += $(CORE_SUPPORT_DIR)/core_cm3.c
#INPUT += $(wildcard $(SRC_DIR)/*.c)

ASM_INPUT = main.c
ASM_INPUT += $(DEVICE_SUPPORT_DIR)/startup/gcc_ride7/startup_stm32f10x_ld.s
ASM_INPUT += $(THREAD_MANAGER_SRC)/threadManager.c

LD = -T./linkerScript.ld

OUTPUT = -o $(TARGET)

main:
	$(CC) $(CC_FLAGS) $(INPUT) $(LD) $(OUTPUT)

assembly:
	$(CC) $(CC_FLAGS) -S $(ASM_INPUT) $(LD)