#ifndef _SCREENBUFFER_H
#define _SCREENBUFFER_H

#include "types.h"

typedef struct
{
    volatile uint32_t physical_width;
    volatile uint32_t physical_height;
    volatile uint32_t virtual_width;
    volatile uint32_t virtual_height;
    volatile uint32_t gpu_pitch;
    volatile uint32_t bit_depth;
    volatile uint32_t x;
    volatile uint32_t y;
    volatile uint32_t gpu_pointer;
    volatile uint32_t gpu_size;
} screenbuffer_t;

int initialize_framebuffer(uint32_t physical_w, uint32_t physical_h, uint32_t virtual_w, uint32_t virtual_h);
void set_pixel(uint32_t x, uint32_t y, uint32_t color);
void clear_framebuffer();
void draw_line(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color);
void display_image(const unsigned int* data, uint32_t width, uint32_t height, uint32_t offset_x, uint32_t offset_y);
void print_buffer_example(void);
void print_rotating_bar_example(void);
#endif
