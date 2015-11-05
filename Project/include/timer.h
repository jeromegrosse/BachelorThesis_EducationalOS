#ifndef _TIMER_H
#define _TIMER_H

#include "types.h"

typedef struct
{
    volatile uint32_t control_status;
    volatile uint32_t counter_low;
    volatile uint32_t counter_high;
    volatile uint32_t compare0;
    volatile uint32_t compare1;
    volatile uint32_t compare2;
    volatile uint32_t compare3;
} systimer_t;

uint64_t get_time_64(void);
void wait_microseconds( uint32_t delay );


#endif
