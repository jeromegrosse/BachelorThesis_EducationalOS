#include "armtimer.h"

volatile armtimer_t *__armtimer = (armtimer_t *)ARM_TIMER0_BASE;

void armtimer_enable(uint32_t prescaler)
{
    __armtimer->control = ARM_TIMER_32BIT_COUNTER | ARM_TIMER_INTERRUPT_ENABLE | ARM_TIMER_ENABLE;
    switch (prescaler)
    {
        case 256:
            __armtimer->control |= ARM_TIMER_PRESCALE_256;
            break;
        case 16:
            __armtimer->control |= ARM_TIMER_PRESCALE_16;
            break;
        case 1:
        default:
            __armtimer->control |= ARM_TIMER_PRESCALE_1;
            break;
    }
}


void armtimer_disable(void)
{
    __armtimer->control |= ARM_TIMER_INTERRUPT_DISABLE | ARM_TIMER_DISABLE;
}


void armtimer_set(uint32_t load)
{
    __armtimer->load   = load;
    __armtimer->reload = load;
}
