#include <stdlib.h>
#include <stdio.h>
#include "base_test.h"
#include "queue.h"
#include "constants.h"
#include "malloc.h"


void queue_init_test(void)
{
    unsigned int error = 0;

    char *heap = (char *)malloc(1024);

    // 1. Build the memory
    memory_init(heap, 1024);

    // 2. Starting test
    queue* q = create_queue();
    error += assert_equals_integer(0, (int)q->size);
    error += assert_equals_integer((int)NULL, (int)q->head);
    error += assert_equals_integer((int)NULL, (int)q->tail);
    memory_free(q);
    memory_destroy();

    free(heap);

    printf("queue_init_test executed with %u errors.\n", error);
}


void queue_enqueue_test(void)
{
    unsigned int error = 0;

    char *heap = (char *)malloc(1024*1024);

    // 1. Build the memory
    memory_init(heap, 1024*1024);

    // 2. Starting test
    queue* q = create_queue();

    // 3. First enqueue
    int element = 5;
    enqueue(q, &element);

    int* queue_element = (int*)q->head->element;
    error += assert_equals_integer(1, (int)q->size);
    error += assert_equals_integer((int)q->head, (int)q->tail);
    error += assert_equals_integer(element, *queue_element);

    // 4. Second enqueue
    int element2 = 10;
    enqueue(q, &element2);
    queue_element = (int*)q->head->element;
    int* queue_element2 = (int*)q->head->next->element;
    int* queue_element_head = (int*)q->head->element;
    int* queue_element_tail = (int*)q->tail->element;
    error += assert_equals_integer(2, (int)q->size);
    error += assert_not_equals_integer((int)q->head, (int)q->tail);
    error += assert_equals_integer(element, *queue_element);
    error += assert_equals_integer(element2, *queue_element2);
    error += assert_equals_integer(*queue_element_head, *queue_element);
    error += assert_equals_integer(*queue_element_tail, *queue_element2);
    memory_free(q);
    memory_destroy();

    free(heap);

    printf("queue_enqueue_test executed with %u errors.\n", error);
}


void queue_dequeue_test(void)
{
    unsigned int error = 0;

    char *heap = (char *)malloc(1024*1024);

    // 1. Build the memory
    memory_init(heap, 1024*1024);

    // 2. Starting test
    queue* q = create_queue();

    int element = 5;
    int element2 = 10;
    enqueue(q, &element);
    enqueue(q, &element2);

    // 3. First dequeue
    int* dequeue_element1 = dequeue(q);
    error += assert_equals_integer(1, (int)q->size);
    error += assert_equals_integer((int)q->head, (int)q->tail);
    error += assert_equals_integer(element, *dequeue_element1);

    // 4. Second dequeue
    int* dequeue_element2 = dequeue(q);
    error += assert_equals_integer(0, (int)q->size);
    error += assert_equals_integer((int)q->head, (int)q->tail);
    error += assert_equals_integer(element2, *dequeue_element2);

    // 5 Third dequeue (queue is empty right now)
    int* dequeue_element3 = dequeue(q);
    error += assert_equals_integer(0, (int)q->size);
    error += assert_equals_integer((int)NULL, (int)dequeue_element3);


    memory_free(q);
    memory_destroy();

    free(heap);

    printf("queue_dequeue_test executed with %u errors.\n", error);
}


int main()
{
    printf("\n\n *** QUEUE TEST ***\n");

    queue_init_test();
    queue_enqueue_test();
    queue_dequeue_test();
}
