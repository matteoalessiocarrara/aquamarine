/* Copyright 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com> */

# include <stdint.h>
# include <stdbool.h>

# include "vga_console.h"

static uint8_t vga_color;
static size_t cursor; // offset

void vga_init() {
	vga_color = vga_color_pair(VGA_COLOR_WHITE, VGA_COLOR_CYAN);
	for (size_t i = 0; i < VGA_CHARS; i++) vga_writec(' ');
}

inline void vga_writec(const char c) {
	VGA_BUFF[cursor++] = vga_make_char(c, vga_color);
	if (cursor == (VGA_WIDTH * VGA_HEIGHT)) cursor = 0; // XXX ugly
}

void vga_writes(const char *s) {
	while(*s) vga_writec(*s++);
}
