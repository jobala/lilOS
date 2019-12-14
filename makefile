OBJECTS = archi386/loader.o kernel/main.o common/port/port.o common/libc/memset.o drivers/monitor/monitor.o \
descriptors/gdt/gdt.o descriptors/gdt/global_desc_table.o \
descriptors/idt/idt.o descriptors/idt/interrupt.o descriptors/idt/interrupt_table.o descriptors/idt/isr.o

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
-nostartfiles -nodefaultlibs -Wall -Wextra -c

LDFLAGS = -T archi386/link.ld -m elf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	grub-mkrescue -o os.iso iso

run: os.iso
	bochs -f bochsrc.bxrc -q

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) kernel.elf os.iso bochslog.txt
