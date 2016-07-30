CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc

CFLAGS = -g -fno-common -O0 \
				-mcpu=cortex-m4 -mthumb \
				-T stm32f429.ld -nostartfiles

PROJECT = gpio
TARGET = $(PROJECT).bin
TARGET_ADDR = 0x8000000

all: $(TARGET)

$(TARGET): main.c startup.c
	$(CC) $(CFLAGS) $^ -o $(PROJECT).elf
	$(CROSS_COMPILE)objcopy -Obinary $(PROJECT).elf $(TARGET)
	$(CROSS_COMPILE)objdump -S $(PROJECT).elf > $(PROJECT).list

flash:
	st-flash write $(TARGET) $(TARGET_ADDR)

debug:
	st-util &
	ddd --debugger $(CROSS_COMPILE)gdb $(PROJECT).elf

clean:
	rm -f *.o *.bin *.elf *.list
