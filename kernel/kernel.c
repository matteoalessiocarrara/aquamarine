/* Copyright 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com> */

# if defined(__linux__)
# error "You are not using a cross-compiler, you will most certainly run into trouble"
# endif

# if !defined(__i386__)
# error "This kernel needs to be compiled with a ix86-elf compiler"
# endif

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdarg.h>

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

struct s_vga_entry {
	char c;
	struct s_vga_color color;
};

struct s_vga_color _vga_color;
uint16_t _vga_cursor; // offset

inline void vga_writec(const char c) {
	((struct s_vga_entry*)(VGA_BUFF + _vga_cursor))->c = c;
	((struct s_vga_entry*)(VGA_BUFF + _vga_cursor))->color = _vga_color;
	if (++_vga_cursor == VGA_CHARS) _vga_scroll();
}

void vga_init() {
	_vga_color = (struct s_vga_color){.fg = VGA_COLOR_WHITE, .bg = VGA_COLOR_CYAN};
	for (register uint16_t i = 0; i < VGA_CHARS; i++) vga_writec(' ');
	_vga_cursor = 0;
}

void _vga_scroll() {
	struct s {uint16_t c[VGA_CHARS - VGA_WIDTH];};
	*(struct s*)VGA_BUFF = *(struct s*)(VGA_BUFF + VGA_WIDTH);
	for(register uint8_t i = 0; i < VGA_WIDTH; i++) {
		((struct s_vga_entry*)(VGA_BUFF + VGA_CHARS - VGA_WIDTH + i))->c = ' ';
		((struct s_vga_entry*)(VGA_BUFF + VGA_CHARS - VGA_WIDTH + i))->color = _vga_color;
	}
	_vga_cursor = VGA_CHARS - VGA_WIDTH;
}

void vga_writes(const char *s) {
	while(*s) vga_writec(*s++);
}

inline void printk(const char *s)
{
	printkv(s, 0);
}

void printkv(const char *format, uint8_t argn, ...) {
	va_list ap;
	va_start(ap, argn); 
	for(;*format;format++) {
		switch(*format) {
			case '%':
				switch (*(format + 1)) {
					// WARNING: non-standard
					case 'b': {
						unsigned int v = va_arg(ap, unsigned int);
						vga_writes("0b");
						for(int8_t i = sizeof(unsigned int) * 8 - 1; i >= 0; i--)
							vga_writec(((v >> i) & 1) + '0');
						}
					break;
					default:
						vga_writec(*(format+1));
				}
				format++;
				break;
			case '\n':
				_vga_cursor = (_vga_cursor/VGA_WIDTH + 1) * VGA_WIDTH;
				break;
			default:
				vga_writec(*format);
		}
	}
	va_end(ap);
}

void kmain()
{
	vga_init();
	for (unsigned i = 0; i < 25; i++)
		printkv("%b\n", 1, i);
	printkv("Hello world! %b", 1, 15);
}
