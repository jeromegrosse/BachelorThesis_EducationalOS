#ifndef _ARMTIMER_H
#define _ARMTIMER_H

#include "constants.h"
#include "types.h"

#define ARM_TIMER_32BIT_COUNTER     (1 << 1)    /* 32 bit counter else, 16 bit counter */
#define ARM_TIMER_PRESCALE_1        (0 << 2)   // 00
#define ARM_TIMER_PRESCALE_16       (1 << 2)   // 01
#define ARM_TIMER_PRESCALE_256      (2 << 2)   // 10
#define ARM_TIMER_INTERRUPT_ENABLE  (1 << 5)
#define ARM_TIMER_INTERRUPT_DISABLE (0 << 5)
#define ARM_TIMER_ENABLE            (1 << 7)
#define ARM_TIMER_DISABLE           (0 << 7)

#define ARM_TIMER0_BASE             ARM_BASE


extern void set_interrupt_vector_handler(void (*handler)(void));

/**
    Define on part 14.2 of the BCM2835 ARM Documentation
*/
typedef struct
{
    volatile uint32_t load;              //0x400￼
    volatile uint32_t value;             //0x404￼
    volatile uint32_t control;           //0x408￼
    volatile uint32_t irq_clear;         //0x40C￼
    volatile uint32_t raw_irq;           //0x410￼
    volatile uint32_t masked_irq;        //0x414￼
    volatile uint32_t reload;            //0x418
    volatile uint32_t predivider;        //0x41C
    volatile uint32_t free_runing_timer; //0x420
} armtimer_t;

extern volatile armtimer_t *__armtimer;


void armtimer_enable(uint32_t prescaler);
void armtimer_disable(void);
void armtimer_set(uint32_t load);

#endif
