#ifndef SCREEN_TEXT_H
#define SCREEN_TEXT_H

#include "types.h"

#define SCREEN_TEXT_COLOR 0xFF00CC00
#define SCREEN_TEXT_BLACK 0xFF000000

void init_screen_text(uint32_t w, uint32_t h);
void st_set_cursor(uint32_t r, uint32_t c);
void st_print_char(char c);
void st_print_string(char* c);
void print_screen_text_example(void);

#endif
