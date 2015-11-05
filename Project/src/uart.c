#include "uart.h"
#include "constants.h"
#include "timer.h"
#include "gpio.h"
#include "strings.h"
#include "malloc.h"
#include "stdio.h"

volatile uart_t *__uart = (uart_t *)UART0_BASE;


void uart_write_char(char c)
{
    while (__uart->fr & (1 << 5)); //Check if the fifo is full by checking the TXFF flag

    __uart->dr = c;
}


void uart_write(char *string)
{
    while (*string != '\0')
    {
        light_act(PIN_ON);
        char c = *string;
        if (c == '\n' || c == 13)
        {
            uart_write_char('\n');
            uart_write_char('\r');
        }
        else { uart_write_char(c); }
        string++;
        light_act(PIN_OFF);
    }
}


char uart_read(void)
{
    char c = '\0';
    if ((__uart->fr & (1 << 4)) == 0)
    {
        c = __uart->dr;
    }
    return c;
}

void uart_init(void)
{
    // Disable pull up/down for all GPIO
    gpio[GPIO_GPPUD] = 0;
    wait_microseconds(150);

    // Disable pull/down for pin 14 and 15
    gpio[GPIO_GPPUDCLK0] = (1 << 14) | (1 << 15);
    wait_microseconds(150);

    // Reset GPPUDCLK0
    gpio[GPIO_GPPUDCLK0] = 0;


    __uart->cr = 0; //Disable UART 0
    __uart->icr = 0x7FF; //Clear interrupts of the UART

    // Setting the baude rate
    __uart->ibrd = 1;
    __uart->fbrd = 40;

    // Enable FIFO, 8 bits
    __uart->lcrh = (1 << 4) | (1 << 5) | (1 << 6);

    // Turning off interrupt
    __uart->imsc = (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10);

    // Control register
    __uart->cr   = (1 << 0) | (1 << 8) | (1 << 9);
}

char* uart_get_input_buffer(void){
    char *buffer = (char *)memory_alloc(sizeof(char) * 17);
    rpi_memset(buffer, '\0', 17);

    uint8_t counter = 0;
    do {
        buffer[counter] = uart_read();
    } while (buffer[counter++] != '\0' && counter < 17);

    return buffer;
}
