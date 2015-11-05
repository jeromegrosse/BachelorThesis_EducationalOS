#include "kernel.h"
#include "stdio.h"
#include "timer.h"
#include "screenbuffer.h"
#include "uart.h"
#include "user_program.h"
#include "constants.h"
#include "screen_text.h"
#include "malloc.h"
#include "gpio.h"



void initialize_hardware(void)
{
    cli();
    uart_init();
    rpi_printf("UART initialized\n");

    if (initialize_framebuffer(1280, 1024, 800, 600) == -1)
    {
        rpi_printf("Error initializing framebuffer");
        while (1);
    }
    print_debug("Frame-buffer initialized with physical resolution:1280x1024 and virtual:800x600");
    rpi_printf("Frame-buffer correctly initialized\n");

    init_screen_text(1280, 1024);
    st_set_cursor(0, 0);
    rpi_printf("Screen-text correctly initialized\n");
}


void initialize_memory(void)
{
    memory_init((void *)HEAP_START_ADDRESS, HEAP_MAX_SIZE);
    rpi_printf("Memory correctly initialized\n");
}

int kernel_main(void)
{
    wait_microseconds(2000000);
    initialize_hardware();
    //light_act(PIN_OFF);
    initialize_memory();

    print_debug("Initialization finished. Starting main program.");

    main_program();

    // main program should never return.
    print_debug("Main program over. Hanging.");
    while (1);

    return 0;
}
