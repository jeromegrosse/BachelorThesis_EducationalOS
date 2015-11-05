#ifndef _MAILBOX_H
#define _MAILBOX_H

#include "constants.h"
#include "types.h"


#define MAILBOX_POWER_MANAGEMENT 0
#define MAILBOX_FRAMEBUFFER      1
#define MAILBOX_VIRTUAL_UART     2
#define MAILBOX_VCHIQ            3
#define MAILBOX_LED              4
#define MAILBOX_BUTTONS          5
#define MAILBOX_TOUCH_SCREEN     6
#define MAILBOX_MAX              6

#define MAILBOX_EMPTY            0x40000000
#define MAILBOX_FULL             0x80000000

#define MAILBOX_BASE             (BCM2708_PERIPHERIRAL_BASE + 0xB880)


typedef struct
{
    volatile uint32_t read;            //0x2000B880
    volatile uint32_t unallocated[3];  //0x2000B884
    volatile uint32_t poll;            //0x2000B890
    volatile uint32_t sender;          //0x2000B894
    volatile uint32_t status;          //0x2000B898
    volatile uint32_t configuration;   //0x2000B89C
    volatile uint32_t write;           //0x2000B8A0
} mailbox_t;

extern volatile mailbox_t *__mailbox;

int mailbox_write(uint32_t channel, uint32_t data);
int mailbox_read(uint32_t channel);

#endif
