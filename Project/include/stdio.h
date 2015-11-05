#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>

#define PRINTF_BUFFER 128

extern void cli();
extern void sei();

void rpi_printf(const char *string, ...);
void rpi_printf_debug(const char *string, ...);
void print_debug(char *string);
void stdio_handle_interrupt(int should_i);
#endif
