#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include "strings.h"
#include "armtimer.h"
#include "stdio.h"
//#include "scheduler.h"


#define ARM_TIMER_IRQ         (1 << 0)
#define ARM_MAILBOX_IRQ       (1 << 1)
#define ARM_DOORBELL_0_IRQ    (1 << 2)
#define ARM_DOORBELL_1_IRQ    (1 << 3)
#define GPU_0_HALTED_IRQ      (1 << 4)
#define GPU_1_HALTED_IRQ      (1 << 5)
#define ACCESS_ERROR_1_IRQ    (1 << 6)
#define ACCESS_ERROR_0_IRQ    (1 << 7)

#define INTERRUPT_CONTROLLER_BASE  0x2000B200

typedef struct
{
    volatile uint32_t irq_basic_pending;
    volatile uint32_t irq_pending_1;
    volatile uint32_t irq_pending_2;
    volatile uint32_t fiq_control;
    volatile uint32_t enable_irqs_1;
    volatile uint32_t enable_irqs_2;
    volatile uint32_t enable_basic_irqs;
    volatile uint32_t disable_irqs_1;
    volatile uint32_t disable_irqs_2;
    volatile uint32_t disable_basic_irqs;
} irq_controller_t;

extern irq_controller_t *__irq_controller;
void (*interrupt_vector_handler)(void);


void sei(void);
void cli(void);

/**
    According to the gcc documentation, we can use the following syntax to declare a interrupt handler:
    void f () __attribute__ ((interrupt ("IRQ")));
*/

/**
    TODO
*/
void __attribute__((interrupt("ABORT"))) reset_vector(void);

/**
    TODO
*/
void __attribute__((interrupt("ABORT"))) prefetch_abort_vector(void);

/**
    TODO
*/
void __attribute__((interrupt("ABORT"))) data_abort_vector(void);

/**
    TODO
*/
void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector(void);

/**
    TODO
*/
void __attribute__((interrupt("SWI"))) software_interrupt_vector(void);

/**
    TODO
*/
void __attribute__((interrupt("IRQ"))) interrupt_vector(void);

/**
    TODO
*/
void __attribute__((interrupt("FIQ"))) fast_interrupt_vector(void);

void enable_armtimer_irq(void);
void disable_armtimer_irq(void);
void set_interrupt_vector_handler(void (*handler)(void));
extern void ENABLE_IRQ(void);
extern void DISABLE_IRQ(void);
#endif
