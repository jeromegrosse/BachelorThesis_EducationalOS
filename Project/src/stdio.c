#include "stdio.h"
#include "strings.h"
#include "uart.h"
#include "malloc.h"
#include "screen_text.h"

int take_care_interupt = 1;

void rpi_printf(const char *string, ...)
{
    if(take_care_interupt == 1) cli(); // Not forbidding to interrupt can create an unalign data access while writing to the GPIO
    va_list arguments;
    va_start(arguments, string);

    char buffer[PRINTF_BUFFER];
    rpi_memset(&buffer[0], 0, PRINTF_BUFFER);

    _sprintf(&buffer[0], string, arguments);
    uart_write(buffer);
    va_end(arguments);
    if(take_care_interupt == 1) sei();
}

void rpi_printf_debug(const char *string, ...)
{
    string = string;
    #ifdef DEBUG
    if(take_care_interupt == 1) cli(); // Not forbidding to interrupt can create an unalign data access while writing to the GPIO
    va_list arguments;
    va_start(arguments, string);

    char buffer[PRINTF_BUFFER];
    rpi_memset(&buffer[0], 0, PRINTF_BUFFER);

    _sprintf(&buffer[0], string, arguments);
    uart_write(buffer);
    va_end(arguments);
    if(take_care_interupt == 1) sei();
    #endif
}


void print_debug(char *string)
{
    string = string;
#ifdef DEBUG
    rpi_printf("DEBUG: %s\n", string);
#endif
}

void stdio_handle_interrupt(int should_i){
    take_care_interupt = should_i;
}
