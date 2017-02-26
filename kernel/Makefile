# Copyright 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com>

HOST = i686-elf

AS = $(HOST)-as
CC = $(HOST)-gcc

CFLAGS = -ffreestanding -O2 -std=gnu99 -Wall -Wextra
KNAME = aquamarine
KBIN = $(KNAME).bin
KISO = $(KNAME).iso
ISOROOT = ../iso/
OBJS = boot.o vga_console.o kernel.o


$(KBIN): $(OBJS)
	$(CC) -T linker.ld $(CFLAGS) -nostdlib -lgcc -o $(KBIN) $(OBJS)
	
kernel.o: kernel.c
	$(CC) -c kernel.c -o kernel.o  $(CFLAGS)

vga_console.o: vga_console.c vga_console.h
	$(CC) -c vga_console.c -o vga_console.o  $(CFLAGS)

boot.o: boot.s
	$(AS) boot.s -o boot.o

clean:
	rm -f $(KBIN) $(KISO) $(ISOROOT)/boot/$(KBIN) $(OBJS)

qemu: $(KBIN)
	qemu-system-x86_64 -kernel $(KBIN)
	
iso: $(KBIN)
	cp $(KBIN) $(ISOROOT)/boot
	grub-mkrescue -o $(KISO) $(ISOROOT)

tmh: $(KBIN)
	grub-file --is-x86-multiboot $(KBIN) && echo "this is a valid multiboot kernel" || echo "invalid multiboot header"
