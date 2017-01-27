# Copyright 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com>

HOST = i686-elf
CFLAGS = -ffreestanding -O2 -std=gnu99 -Wall -Wextra
AS = $(HOST)-as
CC = $(HOST)-gcc
KF = aquamarine.bin
OBJS = kernel.o vga.o boot.o


qemu: $(KF)
	qemu-system-x86_64 -kernel $(KF)


tmh: $(KF)
	grub-file --is-x86-multiboot $(KF) && echo "this is a valid multiboot kernel" || echo "invalid multiboot header"


$(KF): $(OBJS)
	$(CC) -T linker.ld -o $(KF) $(CFLAGS) -nostdlib -lgcc $(OBJS)


kernel.o: kernel.c
	$(CC) -c kernel.c -o kernel.o  $(CFLAGS)
	

vga.o: vga.c vga.h
	$(CC) -c vga.c -o vga.o  $(CFLAGS)


boot.o: boot.s
	$(AS) boot.s -o boot.o


clean:
	rm -f $(KF) *.o
