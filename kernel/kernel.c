# include "vga_console.h"

# if defined(__linux__)
# error "You are not using a cross-compiler, you will most certainly run into trouble"
# endif

# if !defined(__i386__)
# error "This kernel needs to be compiled with a ix86-elf compiler"
# endif


void kmain()
{
	vga_init();
	vga_writes("Hello world!");
}
