# Copyright 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com>

HOST = i686-elf

AS = $(HOST)-as
CC = $(HOST)-gcc

CFLAGS = -ffreestanding -O2 -g -std=gnu99 -Wall -Wextra
KNAME = aquamarine
KBIN = $(KNAME).bin
KISO = $(KNAME).iso
ISOROOT = ../iso/
OBJS = boot/boot.o dev/vga_console.o kernel.o lib/printk.o


$(KBIN): $(OBJS)
	$(CC) -T boot/linker.ld $(CFLAGS) -nostdlib -lgcc -o $(KBIN) $(OBJS)
	
kernel.o: kernel.c
	$(CC) -c kernel.c -o kernel.o  $(CFLAGS)

dev/vga_console.o: dev/vga_console.c dev/vga_console.h
	$(CC) -c dev/vga_console.c -o dev/vga_console.o  $(CFLAGS)

boot/boot.o: boot/boot.s
	$(AS) boot/boot.s -o boot/boot.o

lib/printk.o: lib/printk.h lib/printk.c
	$(CC) -c lib/printk.c -o lib/printk.o $(CFLAGS)
	
clean:
	rm -f $(KBIN) $(KISO) $(ISOROOT)/boot/$(KBIN) $(OBJS)

qemu: $(KBIN)
	qemu-system-x86_64 -kernel $(KBIN)
	
iso: $(KBIN)
	cp $(KBIN) $(ISOROOT)/boot
	grub-mkrescue -o $(KISO) $(ISOROOT)

tmh: $(KBIN)
	grub-file --is-x86-multiboot $(KBIN) && echo "this is a valid multiboot kernel" || echo "invalid multiboot header"
