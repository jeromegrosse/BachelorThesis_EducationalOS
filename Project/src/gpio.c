#include "gpio.h"

//GPIO Pins pointer
volatile uint32_t *gpio = (unsigned int *)GPIO_BASE;

void light_act(int state)
{
    //Light ACT (PIN 47):
    gpio[GPIO_GPFSEL4] = 1 << 7 * 3;

    if (state == PIN_ON) gpio[GPIO_GPSET1] |= 1 << (47 - 32);
    else                 gpio[GPIO_GPCLR1] |= 1 << (47 - 32);
}
