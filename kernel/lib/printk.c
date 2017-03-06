/* Copyright 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com> */
# include <stdarg.h>
# include <stdint.h>

# include "printk.h"
# include "../dev/vga_console.h"

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
				vga_cursor = (vga_cursor/VGA_WIDTH + 1) * VGA_WIDTH;
				break;
			default:
				vga_writec(*format);
		}
	}
	va_end(ap);
}
