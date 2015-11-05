#include "scheduler.h"
#include "malloc.h"
#include "armtimer.h"
#include "arm.h"

#ifndef TEST
#include "interrupts.h"
#endif

pcb_t* _pcb_list = (pcb_t *)0; //This variable is set at address 0 up to the first allocation
pcb_t* _current_pcb;

//Process id
unsigned int pid = 0;


#ifdef TEST
void enable_armtimer_irq() {}
void sei() {}
#endif



void start_process(void)
{
    rpi_printf("Starting process with pid %d with context at address %x.\n", _current_pcb->pid, _current_pcb);
    _current_pcb->state = RUNNING;
    __asm("mov sp, %0" :: "r" (_current_pcb->context.sp));
    _current_pcb->function();
    _current_pcb->state = TERMINATED;
    rpi_printf("Process with pid %d terminated\n", _current_pcb->pid);
    //terminate_process(_current_pcb);
    //_current_pcb = NULL;
    while(1) {
        rpi_printf("Process %d idle.\n", _current_pcb->pid);
    } //Wait until another process get scheduled.
}

void create_process(void (*func) (void), void* args)
{
    print_debug("Creation a process");
    pcb_t *pcb = (pcb_t *)memory_alloc(sizeof(pcb_t));
    if(pcb == NULL) {
        rpi_printf("Warning: Unable to allocate a PCB in the memory (heap full?)\n");
        return ;//No more place in the heap
    }
    pcb->next = NULL;
    print_debug("PCB Allocated");

    if(_pcb_list == 0) {
        print_debug("First process creation detected");
        _pcb_list    = pcb;
        _current_pcb = pcb;
    } else {
        print_debug("Not first process creation");
        pcb_t* pcbl = _pcb_list;
        while(pcbl->next != NULL) pcbl = (pcb_t *)pcbl->next;
        pcbl->next = (struct pcb_t *)pcb;
    }


    pcb->pid         = pid++;
    pcb->state       = NEW;
    pcb->function    = func;
    pcb->arguments   = args;

    char* sp_addr = (char *)memory_alloc(STACK_SIZE);
    if (sp_addr == NULL) {
        rpi_printf("\n\n/!\\ Warning, could not allocated sp stack for process %d.\n\n\n", pcb->pid);
    }
    pcb->context.sp_origin = (unsigned int*) (sp_addr);
    pcb->context.sp  = (unsigned int*) (sp_addr + STACK_SIZE*sizeof(char)); //Descending stack
    pcb->context.lr  = (unsigned int*) start_process;

    rpi_printf("Process with pid %d created and context at %x. Sp: %x, lr: %x, Callback set to %x\n", pcb->pid, pcb, pcb->context.sp, pcb->context.lr, func);
    print_debug("Context correctly created");
}


void terminate_process(pcb_t* pcb_process_to_terminate)
{
    print_debug("Deleting process");
    memory_free(pcb_process_to_terminate->context.sp_origin);
    memory_free(pcb_process_to_terminate);
    print_debug("Process deleted");
}


pcb_t* get_next_pcb(pcb_t* current)
{
    return current->next != NULL ? current->next : _pcb_list;
}


void bootstrap_scheduler(void)
{
    print_debug("Bootstraping scheduler");
    armtimer_set(0xFF);
    enable_armtimer_irq();
    armtimer_enable(256);
    sei();
    start_process();
}


pcb_t* scheduler(void)
{
    pcb_t* pcb = _current_pcb;
#ifdef RR_SCHEDULER
    do {
        pcb = get_next_pcb(pcb);
        if (pcb->pid == _current_pcb->pid && _current_pcb->state == TERMINATED) {
            pcb = NULL;
            break;
        }
    } while(pcb->state == TERMINATED);
#endif

    return pcb;
}


unsigned int get_current_pid(void) {
    return _current_pcb->pid;
}

pcb_t* get_current_pcb(void) {
    return _current_pcb;
}

void set_current_pcb(pcb_t* new_current_pcb) {
    _current_pcb = new_current_pcb;
}
