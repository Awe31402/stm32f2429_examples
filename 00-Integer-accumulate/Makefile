CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc

CMSIS_PATH=../cmsis/
PLATFORM=STM32f429disco

CFLAGS = -g -fno-common -O0 \
				-mcpu=cortex-m4 -mthumb \
				-T stm32f429.ld -nostartfiles

TARGET = hello.bin

all: $(TARGET)

$(TARGET): main.c startup.c
	$(CC) $(CFLAGS) $^ -I$(CMSIS_PATH) -I$(CMSIS_PATH)$(PLATFORM) \
		-o hello.elf
	$(CROSS_COMPILE)objcopy -Obinary hello.elf hello.bin
	$(CROSS_COMPILE)objdump -S hello.elf > hello.list

flash:
	st-flash write hello.bin 0x8000000

debug:
	kill -9 `ps | grep st-util | awk '{print $1}'`
	st-util &
	ddd --debugger $(CROSS_COMPILE)gdb hello.elf

clean:
	rm -f *.o *.bin *.elf *.list
