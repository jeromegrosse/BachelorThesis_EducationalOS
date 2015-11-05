#include "screenbuffer.h"
#include "constants.h"
#include "mailbox.h"
#include "math.h"
#include "stdio.h"
#include "data/uc3m.h"
#include "malloc.h"

volatile screenbuffer_t *__screenbuffer = (screenbuffer_t *) 0x40040000;

int initialize_framebuffer(uint32_t physical_w, uint32_t physical_h, uint32_t virtual_w, uint32_t virtual_h)
{
    print_debug("Initializing framebuffer");

    __screenbuffer->physical_width  = physical_w;
    __screenbuffer->physical_height = physical_h;
    __screenbuffer->virtual_width   = virtual_w;
    __screenbuffer->virtual_height  = virtual_h;
    __screenbuffer->bit_depth       = 32;
    __screenbuffer->gpu_pointer     = 0;


    uint32_t read = 0;
    while (__screenbuffer->gpu_pointer == 0)
    {
        if (mailbox_write(MAILBOX_FRAMEBUFFER, (uint32_t)(__screenbuffer) + 0x40000000) == -1) { return -1; }
        read = mailbox_read(MAILBOX_FRAMEBUFFER);
    }
    return read;
}


void set_pixel(uint32_t x, uint32_t y, uint32_t color)
{
    if (x >= __screenbuffer->virtual_width || y >= __screenbuffer->virtual_height) { return; }

    volatile uint32_t *gp = (uint32_t *)__screenbuffer->gpu_pointer;
    gp[x + y * __screenbuffer->virtual_width] = color;
}


void clear_framebuffer()
{
    volatile uint32_t x, y;
    for (y = 0; y < __screenbuffer->virtual_height; y++)
    {
        for (x = 0; x < __screenbuffer->virtual_width; x++)
        {
            set_pixel(x, y, 0xFF000000);
        }
    }
}


void draw_line(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color)
{
    //Implementation of Bresenham's Algorithm based upon http://www.etechplanet.com/codesnippets/computer-graphics-draw-a-line-using-bresenham-algorithm.aspx
    int x, y, dx, dy, dx2, dy2, px, py, x_error, y_error, i;
    dx = x1 - x0;
    dy = y1 - y0;
    dx2 = abs(dx);
    dy2 = abs(dy);
    px = 2 * dy2 - dx2;
    py = 2 * dx2 - dy2;

    //Fix case where dy = 0
    if (dy2 <= dx2)
    {

        if (dx >= 0)
        {
            x       = x0;
            y       = y0;
            x_error = x1;
        }
        else
        {
            x       = x1;
            y       = y1;
            x_error = x0;
        }

        set_pixel(x, y, color);

        for (i = 0; x < x_error; i++)
        {

            x++;
            if (px < 0)
            {
                px = px + 2 * dy2;
            }
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                {
                    y++;
                }
                else
                {
                    y--;
                }
                px = px + 2 * (dy2 - dx2);
            }

            set_pixel(x, y, color);
        }
    }
    else
    {
        if (dy >= 0)
        {
            x       = x0;
            y       = y0;
            y_error = y1;
        }
        else
        {
            x       = x1;
            y       = y1;
            y_error = y0;
        }
        set_pixel(x, y, color);
        for (i = 0; y < y_error; i++)
        {
            y = y + 1;
            if (py <= 0)
            {
                py = py + 2 * dx2;
            }
            else
            {
                if (( dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                {
                    x++;
                }
                else
                {
                    x--;
                }
                py = py + 2 * (dx2 - dy2);
            }
            set_pixel(x, y, color);
        }
    }
}


void display_image(const unsigned int* data, uint32_t width, uint32_t height, uint32_t offset_x, uint32_t offset_y){
    volatile uint32_t x, y;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            set_pixel(x + offset_x, y + offset_y, data[x + y * width]);
        }
    }
}


void print_buffer_example(void)
{
    print_debug("Displaying UC3M logo on the screen");

    display_image(image_data, 150, 150, 325, 225);
}

void print_rotating_bar_example(void)
{
    print_debug("Displaying rotating bars screen");
    while(1) {
        draw_line(400   ,100  , 400, 500,  0xFF00FF00); // |
        clear_framebuffer();
        draw_line(541 , 441  ,  259, 159,  0xFF00FF00); // \ /
        clear_framebuffer();
        draw_line(200   , 300, 600,  300,  0xFF00FF00); // -
        clear_framebuffer();
        draw_line(259, 441  , 541, 159,  0xFF00FF00);   // /
        clear_framebuffer();
    }
}
