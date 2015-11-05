#include "mailbox.h"

volatile mailbox_t *__mailbox = (mailbox_t *)MAILBOX_BASE;


int mailbox_write(uint32_t channel, uint32_t data)
{
    if ((data & 0xF) != 0) { return -1; }

    //Mailox ready when top bit of status is 0 (check if mailbox is not full)
    while (1)
    {
        if ((__mailbox->status & MAILBOX_FULL) == 0) { break; }
    }

    __mailbox->write = data + channel;
    return 1;
}


int mailbox_read(uint32_t channel)
{
    if (channel > MAILBOX_MAX) { return -1; }

    uint32_t message;

    //Mailbox ready when 31th bit of status is 0 (check if mailbox is not empty)
    while (1)
    {
        while (1)
        {
            if ((__mailbox->status & MAILBOX_EMPTY) == 0) { break; }
        }

        message = __mailbox->read;
        if ((message & 0xF) == channel) { break; }
    }

    return message & 0xFFFFFFF0;
}
