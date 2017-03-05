/* Copyright 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com> */

# include <stdint.h>
# include <stdbool.h>

# include "vga_console.h"



void vga_init() {
	vga_color = vga_color_pair(VGA_COLOR_WHITE, VGA_COLOR_CYAN);
	for (register uint16_t i = 0; i < VGA_CHARS; i++) vga_writec(' ');
	vga_cursor = 0;
}

void vga_scroll() {
	struct s {uint16_t c[VGA_CHARS - VGA_WIDTH];};
	*(struct s*)VGA_BUFF = *(struct s*)(VGA_BUFF + VGA_WIDTH);
	for(register uint8_t i = 0; i < VGA_WIDTH; i++)
		VGA_BUFF[VGA_CHARS - VGA_WIDTH + i] = vga_make_char(' ', vga_color);
	vga_cursor = VGA_CHARS - VGA_WIDTH;
}

void vga_writes(const char *s) {
	while(*s) vga_writec(*s++);
}
