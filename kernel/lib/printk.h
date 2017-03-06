/* Copyright 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com> */
# include <stdint.h>
void printkv(const char *format, uint8_t argn, ...);
inline void printk(const char *s) { printkv(s, 0); }
