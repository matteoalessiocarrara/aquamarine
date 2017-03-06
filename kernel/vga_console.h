/* Copyright 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com> */

# ifndef VGA_CONSOLE_H
# define VGA_CONSOLE_H

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>

# define VGA_WIDTH 80
# define VGA_HEIGHT 25
# define VGA_CHARS (VGA_WIDTH * VGA_HEIGHT)
# define VGA_BUFF ((uint16_t *) 0xB8000)

enum e_vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15
};

struct s_vga_color {
	uint8_t fg : 4;
	uint8_t bg : 4;
};

struct vga_entry {
	char c;
	struct s_vga_color color;
};

struct s_vga_color vga_color;
uint16_t vga_cursor; // offset

void vga_init();
void vga_scroll();
void vga_writes(const char *s);

inline void vga_writec(const char c) {
	((struct vga_entry*)(VGA_BUFF + vga_cursor))->c = c;
	((struct vga_entry*)(VGA_BUFF + vga_cursor))->color = vga_color;
	if (++vga_cursor == VGA_CHARS) vga_scroll();
}

# endif
