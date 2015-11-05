#include "screen_text.h"
#include "character.h"
#include "types.h"

#ifndef TEST
#include "screenbuffer.h"
#else

#endif

uint32_t cursor_row        = 0;
uint32_t cursor_col        = 0;
uint32_t st_width          = 0;
uint32_t st_height         = 0;
uint32_t st_max_cursor_row = 0;
uint32_t st_max_cursor_col = 0;

void init_screen_text(uint32_t w, uint32_t h) {
    st_width = w;
    st_height = h;
    st_max_cursor_row = h / (CHAR_HEIGHT + CHAR_INTERLINE);
    st_max_cursor_col = w / (CHAR_WIDTH);
}


void st_set_cursor(uint32_t r, uint32_t c) {
    cursor_row = r;
    cursor_col = c;
}


void st_print_char(char c) {
    uint32_t x_offset = cursor_col * CHAR_WIDTH;
    uint32_t y_offset = cursor_row * (CHAR_HEIGHT + CHAR_INTERLINE);
    uint32_t x,y;

    switch(c) {
        case NL: //\n
            // We could also choose to only change of row
            cursor_col = 0;
            cursor_row++;
            break;

        default:
            for (x = 0; x < CHAR_WIDTH; ++x)
            {
                for (y = 0; y < CHAR_HEIGHT; ++y)
                {
                    set_pixel(x + x_offset, y + y_offset, char_get_pixel(c, x, y) > 0 ? SCREEN_TEXT_COLOR : SCREEN_TEXT_BLACK);
                }
            }
            break;
    }
}

void st_print_string(char* c) {
    uint32_t counter = 0;
    while(c[counter] != '\0') {
        st_print_char(c[counter]);
        cursor_col++;

        if (cursor_col >= st_max_cursor_col) {
            cursor_row++;
        }

        if(cursor_row >= st_max_cursor_row) {
            cursor_row = 0;
        }
        counter++;
    }
}


void print_screen_text_example(void) {
    st_print_string("...\n");
    st_print_string("Wake up, Neo.\n");
    st_print_string("The Matrix has you.\n");
    st_print_string("Follow the white rabbit.\n");
    st_print_string("Knock, knock.\n");
}
