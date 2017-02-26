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

enum vga_color {
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

inline uint16_t vga_make_char(unsigned char c, uint8_t color_pair) {
	return (uint16_t) c | (uint16_t) color_pair << 8;
}

inline uint8_t vga_color_pair(uint8_t fg, uint8_t bg) {
	// WARNING: Depending on the mode setup, attribute bit 7 may be either the 
	// blink bit or the fourth background color bit (which allows all 16 colors 
	// to be used as background colours).
	return fg | bg << 4;
}

void vga_init();
void vga_writec(const char c);
void vga_writes(const char *s);

# endif
