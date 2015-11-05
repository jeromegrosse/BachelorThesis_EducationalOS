#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#define STACK_SIZE 2048
#define RR_SCHEDULER

typedef enum {NEW, READY, RUNNING, WAITING, TERMINATED} State;

// Definition of a context
typedef struct {
    unsigned int* sp_origin; // Origin of the stack pointer,
                             // needed for context destruction
    unsigned int* sp;        // Stack pointer
    unsigned int* lr;        // Link register
} context_t;


// Definition of the process control block
struct pcb_t {
    unsigned int  pid;                 // Process indentifier
    State         state;               // State of the process (new, ready, etc.)
    unsigned int  priority;            //The lower the more priority, linux convention
    void          (*function) (void);  // Function that the process will run
    void*         arguments;           // Arguments to be passed to the function
    context_t     context;
    struct pcb_t  *next;               // Next PCB in the single list
};

typedef struct pcb_t pcb_t;


void start_process(void);
void create_process(void (*func) (void), void* args);
void terminate_process(pcb_t* pcb_process_to_terminate);
pcb_t* get_next_pcb(pcb_t* current);
void bootstrap_scheduler(void);
pcb_t* scheduler(void);
void __attribute__((naked)) context_switch(void);
unsigned int get_current_pid(void);
pcb_t* get_current_pcb(void);
void set_current_pcb(pcb_t* new_current_pcb);
void reset_pid(void);

#endif
