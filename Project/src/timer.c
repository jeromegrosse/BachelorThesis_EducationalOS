#include "timer.h"
#include "constants.h"
#include "types.h"

volatile systimer_t *__systimer = (systimer_t *)SYSTIMER_BASE;


uint64_t get_time_64(void)
{
    return ((uint64_t)__systimer->counter_high) << 32 | __systimer->counter_low;
}


void wait_microseconds( uint32_t delay )
{
    volatile uint32_t start = get_time_64();
    while ( ( get_time_64() - start ) < delay );
}
