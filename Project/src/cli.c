#include "cli.h"
#include "malloc.h"
#include "uart.h"
#include "strings.h"
#include "stdio.h"
#include "screenbuffer.h"

void command_line(void) {
    char buffer_line[MAX_LINE];
    int cli_buffer_counter;
    char c;

    while(1) {
        cli_buffer_counter = 0;
        rpi_memset(buffer_line, '\0', MAX_LINE);
        rpi_printf("%s", PREFIX_LINE);

        // Get command
        while(1) {
            c = uart_read();
            if (cli_buffer_counter > MAX_LINE) c = '\r'; // Reaching max line is the same as pressing enter
            if (c == '\r') {
                // Empty uart buffer
                while(uart_read() != '\0');

                uart_write_char('\n');
                uart_write_char('\r');
                break;
            }
            if (c != '\0') {
                buffer_line[cli_buffer_counter++] = c;
                uart_write_char(c);
            }
        }

        char function[MAX_LINE];
        char argument[MAX_LINE];
        get_first_word(buffer_line, function);
        rpi_strcpy(buffer_line+rpi_strlen(function), argument, MAX_LINE-rpi_strlen(function));

        if(rpi_strcmp("echo", function)) echo(argument);
        else if(rpi_strcmp("show_logo", function)) show_logo();
        else if(rpi_strcmp("show_rotating_bars", function)) show_rotating_bars();
        else if(rpi_strcmp("help", function)) help();
        else rpi_printf("Unrecognized command\n");
    }
}

void echo(char* str) {
    char str_trim[MAX_LINE];
    rpi_trim(str, str_trim);
    rpi_printf("%s\n", str_trim);
}

void show_logo(void) {
    print_buffer_example();
}

void show_rotating_bars(void) {
    print_rotating_bar_example();
}


void help(void) {
    rpi_printf("Available commands:\n");
    rpi_printf("    help - Displays this help message.\n");
    rpi_printf("    echo - Mirror argument to standard serial output.\n");
    rpi_printf("    show_logo - Display image logo on the screen.\n");
    rpi_printf("    show_rotating_bars - Show rotating bar animation example on the screen.\n");
}
