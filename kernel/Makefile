# Copyright 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com>

HOST = i686-elf
AS = $(HOST)-as
CC = $(HOST)-gcc
KF = aquamarine.bin


qemu: $(KF)
	qemu-system-x86_64 -kernel $(KF)


tmh: $(KF)
	grub-file --is-x86-multiboot $(KF) && echo "this is a valid multiboot kernel" || echo "invalid multiboot header"


$(KF): kernel.o boot.o
	$(CC) -T linker.ld -o $(KF) -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc


kernel.o: kernel.c
	$(CC) -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra


boot.o: boot.s
	$(AS) boot.s -o boot.o


clean:
	rm -f $(KF) *.o
