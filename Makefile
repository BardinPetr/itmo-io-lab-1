QEMU = qemu-system-riscv32
TOOLPREFIX = /usr/bin/riscv32-unknown-elf-
CC = ${TOOLPREFIX}gcc
AS = ${TOOLPREFIX}gas
LD = ${TOOLPREFIX}ld
OBJCOPY = ${TOOLPREFIX}objcopy
OBJDUMP = ${TOOLPREFIX}objdump

CFLAGS=-std=c11 -O2 -g3 -Wall -Wextra -ffreestanding -nostdlib

SOURCES=$(wildcard src/*.c)

kernel.elf: kernel.ld ${SOURCES}
	${CC} ${CFLAGS} -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf -Iinclude/ \
		${SOURCES}

qemu: kernel.elf
	${QEMU} \
	  -machine virt \
	  -smp 2 \
	  -bios default \
	  -nographic -serial mon:stdio \
	  --no-reboot \
	  -bios bin/opensbi.bin \
	  -kernel kernel.elf

clean:
	rm -f kernel.elf kernel.map

all: kernel.elf

.PHONY: qemu clean all
