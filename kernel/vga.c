/* Copyright 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com> */

# include <stdint.h>
# include <stdbool.h>

# include "vga.h"


static vga_color_pair term_color;
static size_t term_cursor; // offset


inline vga_color_pair
vga_get_color_pair(vga_color fg, vga_color bg)
{
	return fg | bg << 4;
}


inline vga_char
vga_make_char(unsigned char c, vga_color_pair color)
{
	return (uint16_t) c | (uint16_t) color << 8;
}


void
term_clear()
{
	for (size_t i = 0; i < (TERM_WIDTH * TERM_HEIGHT); i++)
			VGA_MEM[i] = vga_make_char(' ', term_color);
}


void
term_init()
{
	term_color = vga_get_color_pair(VGA_COLOR_WHITE, VGA_COLOR_CYAN);
	term_clear();
}


// called by external functions, since term_color is static
void
term_setcolor(vga_color_pair color)
{
	term_color = color;
}


bool
term_putcharat(char c, size_t x, size_t y)
{
	if ((x < TERM_WIDTH) && (y < TERM_HEIGHT))
	{
		VGA_MEM[y * TERM_WIDTH + x] = vga_make_char(c, term_color);
		return true;
	}
	else
		return false;
}


inline size_t
term_get_cursor_x()
{
	return term_cursor % TERM_WIDTH;
}


inline size_t
term_get_cursor_y()
{
	return term_cursor / TERM_WIDTH;
}


void
term_putchar(char c)
{
	term_putcharat(c, term_get_cursor_x(), term_get_cursor_y());
	
	// XXX ugly
	if (++term_cursor == (TERM_WIDTH * TERM_HEIGHT))
		term_cursor = 0;
}


void term_write(const char *str)
{
	while(*str) term_putchar(*str++);
}
