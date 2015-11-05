// 9 Pulse Width Modulator from BCM2835 Peripheral documentation

#ifndef PWM_H
#define PWM_H

#include "constants.h"
#include "stdio.h"

#define PWM_BASE          (BCM2708_PERIPHERIRAL_BASE + 0x20C000)
#define CLOCK_BASE        (BCM2708_PERIPHERIRAL_BASE + 0x101000)

#define BCM2835_PWMCLK_CNTL   40
#define BCM2835_PWMCLK_DIV    41

// Control MASK
#define BCM2835_PWM1_MS_MODE        (1 << 15)  /* Run in MS mode:                  0 - PWM algorithm,             1 - M/S transmission                         */
#define BCM2835_PWM1_USEFIFO        (1 << 13)  /* Transmission Mode:               0 - Data register,             1 - FIFO                                     */
#define BCM2835_PWM1_POLARITY       (1 << 12)  /* Reverse polarity, 0 - Normal (0 low, 1 high),                   1 - Reversed                                 */
#define BCM2835_PWM1_SILENCEBIT     (1 << 11)  /* Ouput Off state                                                                                              */
#define BCM2835_PWM1_REPEATLASTDATA (1 << 10)  /* Repeat last value if FIFO empty: 0 - Interrupt when FIFO empty, 1 - Last data in FIFO transmitted repeatidly */
#define BCM2835_PWM1_MODE           (1 <<  9)  /* Run in serial mode:              0 - PWM,                       1 - Serial                                   */
#define BCM2835_PWM1_ENABLE         (1 <<  8)  /* Channel Enable:                  0 - Disabled                   1 - Enabled                                  */

#define BCM2835_PWM0_MS_MODE        (1 <<  7)  /* Run in MS mode:                  0 - PWM algorithm,             1 - M/S transmission                         */
#define BCM2835_PWM0_CLEARFIFO      (1 <<  6)  /* Clear FIFO:                      0 - No effects                 1 - Clears                                   */
#define BCM2835_PWM0_USEFIFO        (1 <<  5)  /* Transmission Mode:               0 - Data register,             1 - FIFO                                     */
#define BCM2835_PWM0_POLARITY       (1 <<  4)  /* Reverse polarity:                0 - Normal (0 low, 1 high),    1 - Reversed                                 */
#define BCM2835_PWM0_SILENCEBIT     (1 <<  3)  /* Ouput Off state                                                                                              */
#define BCM2835_PWM0_REPEATLASTDATA (1 <<  2)  /* Repeat last value if FIFO empty: 0 - Interrupt when FIFO empty, 1 - Last data in FIFO transmitted repeatidly */
#define BCM2835_PWM0_MODE           (1 <<  1)  /* Run in serial mode:              0 - PWM,                       1 - Serial                                   */
#define BCM2835_PWM0_ENABLE         (1 <<  0)  /* Channel Enable:                  0 - Disabled                   1 - Enabled                                  */


#define BCM2835_STA4  (1 << 12)
#define BCM2835_STA3  (1 << 11)
#define BCM2835_STA2  (1 << 10)
#define BCM2835_STA1  (1 <<  9)
#define BCM2835_BERR  (1 <<  8)
#define BCM2835_GAPO4 (1 <<  7)
#define BCM2835_GAPO3 (1 <<  6)
#define BCM2835_GAPO2 (1 <<  5)
#define BCM2835_GAPO1 (1 <<  4)
#define BCM2835_RERR1 (1 <<  3)
#define BCM2835_WERR1 (1 <<  2)
#define BCM2835_EMPT1 (1 <<  1)
#define BCM2835_FULL1 (1 <<  0)


// Control and Status Register
typedef struct
{
    volatile uint32_t pwm_control; //0x00￼
    volatile uint32_t pwm_status;  //0x04
    volatile uint32_t pwm_dmac;    //0x08
    volatile uint32_t padding_1;   //0x0C
    volatile uint32_t pwm0_range;  //0x10
    volatile uint32_t pwm0_data;   //0x14￼
    volatile uint32_t pwm_fifo;    //0x18
    volatile uint32_t padding_2;   //0x1C
    volatile uint32_t pwm1_range;  //0x20￼
    volatile uint32_t pwm1_data;   //0x24
} pwm_t;

pwm_t *__pwm = (pwm_t *) PWM_BASE;


volatile uint32_t *__clock = (unsigned int *)CLOCK_BASE;

void audio_init(void)
{
    // Rest clock and pwm
    __clock[BCM2835_PWMCLK_CNTL] = ARM_PM_PASSWD | (1 << 5);
    __pwm->pwm_control = 0;

    // Set up divisor and clock mode
    uint32_t idiv = 2;
    __clock[BCM2835_PWMCLK_DIV]  = ARM_PM_PASSWD | (idiv << 14); // Integer part of divisor
    __clock[BCM2835_PWMCLK_CNTL] = ARM_PM_PASSWD | (1 << 4) | 1;

    //Set up PWM0 and PWM1
    __pwm->pwm0_range = 1024;
    __pwm->pwm1_range = 1024;

    //Enable both PWM, activate FIFO mode and clear FIFO
    __pwm->pwm_control = BCM2835_PWM1_USEFIFO | BCM2835_PWM1_ENABLE | BCM2835_PWM0_USEFIFO | BCM2835_PWM0_ENABLE | BCM2835_PWM0_CLEARFIFO;

    print_debug("Audio hardware initialized");
}


void audio_example(void)
{
    uint32_t i = 0;
    while(1)
    {
        if ((__pwm->pwm_status & BCM2835_FULL1)== 0) {
            rpi_printf("Writing %d to Audio FIFO\n", i);
            __pwm->pwm_fifo = 20*(i & 0x1F);
            i++;
        }
    }
}

#endif
