/* Copyright 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com> */


# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>


# define TERM_WIDTH 80
# define TERM_HEIGHT 25
# define VGA_MEM ((uint16_t *) 0xB8000)


typedef uint8_t vga_color_pair;
typedef uint16_t vga_char;
typedef enum e_vga_color 
{
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
} vga_color;


vga_color_pair vga_get_color_pair(vga_color fg, vga_color bg);
vga_char vga_make_char(unsigned char c, vga_color_pair color);
size_t term_get_cursor_x();
size_t term_get_cursor_y();
void term_clear();
void term_init();
void term_setcolor(vga_color_pair color);
bool term_putcharat(char c, size_t x, size_t y);
void term_putchar(char c);
void term_write(const char *str);



