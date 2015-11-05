#include "character.h"

char char_get_pixel(uint8_t c, uint32_t x, uint32_t y)
{
    if(c < CHAR_FIRST_PRINTABLE_INDEX || x > CHAR_WIDTH) {
        return 0;
    }

    uint8_t line_char = font_data[c][y];
    return (line_char >> x) % 2;
}
