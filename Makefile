PREFIX		= arm-none-eabi-
AS    		= $(PREFIX)as
LD    		= $(PREFIX)ld
GDB   		= $(PREFIX)gdb
CC	  		= $(PREFIX)gcc
CFLAGS 		= -g -O1 -ffreestanding -Wall
LDFLAGS 	= -nostdlib -T ld_ram.lds
TARGET_ARCH = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 
CPPFLAGS    = -ICMSIS/Device/ST/STM32L4xx/Include -ICMSIS/Include

ASFILES  	= crt0.s
CFILES   	= main.c init.c led.c uart.c matrix.c irq.c buttons.c timer.c clocks.c
OFILES 		= main.o crt0.o init.o led.o clocks.o uart.o matrix.o image.o irq.o buttons.o timer.o
PROG 		= main

all: $(PROG) 

.PHONY: connect debug clean

# %.o: %.s
# 	$(AS) crt0.s -o crt0.o

# %.o: %.c 
# 	$(CC) -c $(CFLAGS) $(TARGET_ARCH) $^ -o $@

$(PROG):$(OFILES)
	$(CC) $(LDFLAGS) $^ -o $@

image: 
	arm-none-eabi-objcopy -I binary -O elf32-littlearm -B armv7e-m image.raw image.o

startgdbserver:
	sh ./stty.sh
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

clean:
	rm -f main.o crt0.o init.o led.o uart.o matrix.o irq.o buttons.o timer.o clocks.o
	rm -f main