#include "interrupts.h"
#include "stdio.h"
#include "armtimer.h"
#include "uart.h"
#include "timer.h"
#include "gpio.h"
#include "scheduler.h"
#include "arm.h"
#include "types.h"
#include "malloc.h"


extern void context_switch(void);
extern void ENABLE_IRQ(void);
extern void DISABLE_IRQ(void);


int light_act_state = PIN_OFF;
irq_controller_t *__irq_controller = (irq_controller_t *) INTERRUPT_CONTROLLER_BASE;
uint64_t last_time_light_act_switch = 0;
pcb_t* current_pcb;
volatile pcb_t* pcb_to_switch;

void sei(void)
{
    ENABLE_IRQ();
}


void cli(void)
{
    DISABLE_IRQ();
}

/**
    According to the gcc documentation, we can use the following syntax to declare a interrupt handler:
    void f () __attribute__ ((interrupt ("IRQ")));
*/

/**
    TODO
*/
void __attribute__((interrupt("ABORT"))) reset_vector(void)
{
    cli();
    rpi_printf("Reset vector");
    sei();
}


/**
    TODO
*/
void __attribute__((interrupt("ABORT"))) prefetch_abort_vector(void)
{
    cli();
    rpi_printf("Prefect vector");
    sei();
}


/**
    TODO
*/
void __attribute__((interrupt("ABORT"))) data_abort_vector(void)
{
    cli();
    rpi_printf("Data abort vector\n");

    //Get faulty address http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.faqs/ka11167.html
    uint32_t instruction_adress = 0;
    __asm("mov %0, r14" : "=r" (instruction_adress));
    rpi_printf("Instruction at address %x caused the data abort\n", (instruction_adress - 8));
    while (1);
    sei();
}


/**
    TODO
*/
void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector(void)
{
    cli();
    while (1);
    sei();
}


/**
    TODO
*/
void __attribute__((interrupt("SWI"))) software_interrupt_vector(void)
{
    cli();
    while (1);
    sei();
}


/*
 * asm ( "assembly code"
 *            : output operands                  // optional
 *            : input operands                   // optional
 *            : list of clobbered registers      // optional
 * );
 * Documentation:
 * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0040d/Cacbacic.html
 */
/**
    TODO
*/
void __attribute__((interrupt("IRQ"))) interrupt_vector(void)
{
    cli();
    __armtimer->irq_clear = 1;
    print_debug("Tick");
    stdio_handle_interrupt(0);

    light_act(light_act_state);
    light_act_state = light_act_state == PIN_ON ? PIN_OFF : PIN_ON;

    // Context switch
    pcb_to_switch = scheduler();
    current_pcb = get_current_pcb();
    if (pcb_to_switch != NULL && (current_pcb == NULL || current_pcb->pid != pcb_to_switch->pid))
    {
        if (current_pcb != NULL && current_pcb->state == RUNNING) {
            current_pcb->state = READY;
        }

        if (current_pcb != NULL) {
            rpi_printf_debug("Switching from process %d (%x) to process %d (%x)(%x)(%x)\n", current_pcb->pid, current_pcb, pcb_to_switch->pid, pcb_to_switch, (pcb_to_switch->context.sp), (pcb_to_switch->context.lr));
            __asm("cps #0x13"); // Switch to program mode in order to access the registers and stack pointer
            __asm("push {r0-r12}");
            __asm("mov %0, sp" : "=r" (current_pcb->context.sp));
            __asm("mov %0, lr" : "=r" (current_pcb->context.lr));
        }

        // Restore saved context
        __asm("mov sp, %0" :: "r" (pcb_to_switch->context.sp));
        __asm("mov lr, %0" :: "r" (pcb_to_switch->context.lr));
        if (pcb_to_switch->state != NEW) {
            __asm("pop {r0-r12}");
        }
        __asm("cps #0x12"); // Switch to program mode in order to access the registers and stack pointer
        if (current_pcb != NULL) {
            rpi_printf_debug("Context backed up(%x): sp: %x, lr: %x\n", current_pcb, current_pcb->context.sp, current_pcb->context.lr);
        }
        rpi_printf_debug("Context restored(%x): sp: %x, lr: %x\n", pcb_to_switch, pcb_to_switch->context.sp, pcb_to_switch->context.lr);
        set_current_pcb((pcb_t*) pcb_to_switch);
        pcb_to_switch->state = RUNNING;
    } else if (pcb_to_switch == NULL) {
        rpi_printf("No more tasks to schedule. Hanging...\n");
        char c = '|';
        char progress[] = {'\n', '\n'};
        while (1) {
            switch (c) {
                case '|':
                    c = '/';
                    break;
                case '/':
                    c = '-';
                break;
                case '-':
                    c = '\\';
                break;
                case '\\':
                    c = '|';
                break;
            }
            progress[0] = c;
            rpi_printf("%s\n", progress);
        }
    }

    stdio_handle_interrupt(1);
    print_debug("Tack");
    __armtimer->irq_clear = 1;
    sei();
}


/**
    TODO
*/
void __attribute__((interrupt("FIQ"))) fast_interrupt_vector(void)
{
    cli();
    rpi_printf("Fast interrupt vector");
    sei();
}


void enable_armtimer_irq(void)
{
    __irq_controller->enable_basic_irqs |= ARM_TIMER_IRQ;
}


void disable_armtimer_irq(void)
{
    __irq_controller->enable_basic_irqs |= ~ARM_TIMER_IRQ;
}


void set_interrupt_vector_handler(void (*handler)(void))
{
    interrupt_vector_handler = handler;
}
