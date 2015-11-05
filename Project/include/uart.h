#ifndef _UART_H
#define _UART_H

#include "types.h"

typedef struct
{
    uint32_t dr;           // 0x00 Data Register
    uint32_t rsrecr;       // 0x04
    uint32_t padding1[4];  // -
    uint32_t fr;           // 0x18 Flag Register
    uint32_t padding2;     //
    uint32_t ilpr;         // 0x20 Not in use
    uint32_t ibrd;         // 0x24 Integer baud rate divisor
    uint32_t fbrd;         // 0x28 Fractional baud rate divisor
    uint32_t lcrh;         // 0x2C Line control register
    uint32_t cr;           // 0x30 Control Register
    uint32_t ifls;         // 0x34 Interrupt FIFO Level Select Register
    uint32_t imsc;         // 0x38 Interrupt mask set clear register
    uint32_t ris;          // 0x3C Raw interrupt status register
    uint32_t mis;          // 0x40 Masked interrupt status register
    uint32_t icr;          // 0x44 Interrupt clear Register
    uint32_t dmacr;        // 0x48 DMA control register
    uint32_t padding3[13]; // -
    uint32_t itcr;         // 0x80 Test control register
    uint32_t itip;         // 0x84 Integration test input reg
    uint32_t itop;         // 0x88 Integration test output reg
    uint32_t tdr;          // 0x8C Test data reg
} uart_t;

void uart_write_char(char c);
void uart_write(char *string);
char uart_read(void);
void uart_init(void);
char* uart_get_input_buffer(void);

#endif
