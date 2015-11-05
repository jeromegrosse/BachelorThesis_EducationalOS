#ifndef _PM_H
#define _PM_H

volatile uint32_t *__watchdog = (uint32_t *)ARM_PM_WATCHDOG;
volatile uint32_t *__rstc     = (uint32_t *)ARM_PM_RSTC; //Reset controller


void reboot(void) {
    *__watchdog = ARM_PM_PASSWD | 1;
    *__rstc = ARM_PM_PASSWD | PM_RSTC_WRCFG_FULL_RESET;

    while(1); //Wait for the timeout, at the end of it, the raspberry should restart
}


#endif
