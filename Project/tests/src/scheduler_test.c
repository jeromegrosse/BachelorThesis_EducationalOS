#include "../base_test.h"
#include "../../include/scheduler.h"

#define HEAP_SIZE_SCHEDULER_TEST 1024*1024

void dummy(void) {};

void create_process_test(void)
{
    char *heap = (char *)malloc(HEAP_SIZE_SCHEDULER_TEST);
    rpi_memset(heap, 0, HEAP_SIZE_SCHEDULER_TEST);
    memory_init(heap, HEAP_SIZE_SCHEDULER_TEST);

    unsigned int error = 0;

    // 1 - First process
    create_process(dummy, NULL);

    error += assert_not_equals_integer((int)NULL, (int)pcb_list);
    error += assert_equals_integer(0,             pcb_list->pid);
    error += assert_equals_integer(NEW,           pcb_list->state);
    error += assert_equals_integer((int)NULL,     (int)pcb_list->next);

    // 2 - Second process
    create_process(dummy, NULL);

    error += assert_not_equals_integer((int)NULL, (int)pcb_list->next);
    error += assert_equals_integer(1,             pcb_list->next->pid);
    error += assert_equals_integer(NEW,           pcb_list->next->state);
    error += assert_equals_integer((int)NULL,     (int)pcb_list->next->next);

    // 3 - Third process
    create_process(dummy, NULL);

    error += assert_not_equals_integer((int)NULL, (int)pcb_list->next->next);
    error += assert_equals_integer(2,             pcb_list->next->next->pid);
    error += assert_equals_integer(NEW,           pcb_list->next->next->state);
    error += assert_equals_integer((int)NULL,     (int)pcb_list->next->next->next);


    free(heap);
    pcb_list = 0;
    pid = 0;

    printf("create_process_test executed with %u errors.\n", error);
}


void get_next_pcb_test()
{
    char *heap = (char *)malloc(HEAP_SIZE_SCHEDULER_TEST);
    rpi_memset(heap, 0, HEAP_SIZE_SCHEDULER_TEST);
    memory_init(heap, HEAP_SIZE_SCHEDULER_TEST);

    unsigned int error = 0;

    // 1 - First process
    create_process(dummy, NULL);
    pcb_t *pcb0 = pcb_list;
    create_process(dummy, NULL);
    pcb_t *pcb1 = pcb_list->next;
    create_process(dummy, NULL);
    pcb_t *pcb2 = pcb_list->next->next;

    error += assert_equals_integer(1, get_next_pcb(pcb0)->pid);
    error += assert_equals_integer(2, get_next_pcb(pcb1)->pid);
    error += assert_equals_integer(0, get_next_pcb(pcb2)->pid);

    free(heap);
    pcb_list = 0;
    pid      = 0;

    printf("get_next_pcb_test executed with %u errors.\n", error);
}


void context_switch_test()
{
    char *heap = (char *)malloc(HEAP_SIZE_SCHEDULER_TEST);
    rpi_memset(heap, 0, HEAP_SIZE_SCHEDULER_TEST);
    memory_init(heap, HEAP_SIZE_SCHEDULER_TEST);

    unsigned int error = 0;

    // 1 - First process
    create_process(dummy, NULL);
    create_process(dummy, NULL);
    create_process(dummy, NULL);


    error += assert_equals_integer(0, current_pcb->pid);

    scheduler();
    error += assert_equals_integer(1, current_pcb->pid);

    scheduler();
    error += assert_equals_integer(2, current_pcb->pid);

    scheduler();
    error += assert_equals_integer(0, current_pcb->pid);

    free(heap);
    pcb_list = 0;
    pid = 0;

    printf("context_switch_test executed with %u errors.\n", error);
}


int main()
{
    printf("\n\n *** SCHEDULER TEST ***\n");

    create_process_test();
    get_next_pcb_test();
    context_switch_test();
}
