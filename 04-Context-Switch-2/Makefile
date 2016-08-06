CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc

INCLUDE_PATH =../include
CMSIS_PATH = $(INCLUDE_PATH)/cmsis
HAL_PATH=$(INCLUDE_PATH)/stm32f4-hal

DEFINE+=STM32F429xx

PLATFORM=STM32f429disco

CFLAGS = -g -fno-common -O0 \
				-mcpu=cortex-m4 -mthumb \
				-T stm32f429.ld -nostartfiles

PROJECT=context-switch
TARGET = $(PROJECT).bin

all: $(TARGET)

$(TARGET): main.c startup.c context_switch.S syscall.S
	$(CC) $(CFLAGS) $^ -I$(CMSIS_PATH) -I$(HAL_PATH) -D$(DEFINE) \
		-o $(PROJECT).elf
	$(CROSS_COMPILE)objcopy -Obinary $(PROJECT).elf $(PROJECT).bin
	$(CROSS_COMPILE)objdump -S $(PROJECT).elf > $(PROJECT).list

flash:
	$(shell `ps | grep st-util | awk '{print $1}' | xargs kill -9`)
	st-flash write $(PROJECT).bin 0x8000000

debug:
	$(shell `ps | grep st-util | awk '{print $1}' | xargs kill -9`)
	st-util &
	ddd --debugger $(CROSS_COMPILE)gdb $(PROJECT).elf

emu:
	qemu-system-gnuarmeclipse -board STM32F429I-Discovery --image $(PROJECT).bin

emu_debug:
	ddd --debugger $(CROSS_COMPILE)gdb $(PROJECT).elf &
	qemu-system-gnuarmeclipse -board STM32F429I-Discovery --image $(PROJECT).bin -s -S


clean:
	rm -f *.o *.bin *.elf *.list
