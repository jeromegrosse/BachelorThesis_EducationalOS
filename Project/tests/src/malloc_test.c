#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "malloc_test.h"

void memory_test_init(void)
{
    unsigned int error = 0;

    char *heap = (char *)malloc(1024);
    heap_t* heap_list_test = get_heap_list();

    // 1. Memory init
    memory_init(heap, 1024);
    error += assert_equals_integer((unsigned int)heap_top,       (unsigned int)heap);
    error += assert_equals_integer((unsigned int)heap_top + 1024, (unsigned int)heap_limit);
    error += assert_equals_integer(0, (int)heap_list_test);

    free(heap);

    printf("memory_test_init executed with %u errors.\n", error);
}


void memory_test_four_alloc(void)
{
    unsigned int error = 0;

    char *heap = (char *)malloc(1024);
    heap_t* heap_list_test;

    // 1. Memory init
    memory_init(heap, 1024);


    // 2. Allocation
    int size_memory_1 = 1;
    char *memory1 = memory_alloc(size_memory_1);
    heap_list_test = get_heap_list();
    error += assert_equals_integer((uint32_t)(heap),                                         (uint32_t)heap_list_test);
    error += assert_equals_integer((uint32_t)(heap_list_test + sizeof(heap_t)),                   (uint32_t)memory1);
    error += assert_equals_integer(size_memory_1,                                            (uint32_t)heap_list_test->size);
    error += assert_equals_integer(ALLOCATED,                                                (uint32_t)heap_list_test->allocated);
    error += assert_equals_integer((uint32_t)(heap_list_test + (sizeof(heap_t) + size_memory_1)), (uint32_t)heap_list_test->next);
    error += assert_equals_integer(0,                                                        (uint32_t)heap_list_test->next->next);

    int size_memory_2 = 2;
    char *memory2 = memory_alloc(size_memory_2);
    heap_list_test = get_heap_list();
    error += assert_equals_integer((uint32_t)(heap_list_test->next + sizeof(heap_t)),             (uint32_t)memory2);
    error += assert_equals_integer(size_memory_2,                                            (uint32_t)heap_list_test->next->size);
    error += assert_equals_integer(ALLOCATED,                                                (uint32_t)heap_list_test->next->allocated);
    error += assert_equals_integer(0,                                                        (uint32_t)heap_list_test->next->next->next);

    int size_memory_3 = 3;
    char *memory3 = memory_alloc(size_memory_3);
    heap_list_test = get_heap_list();
    error += assert_equals_integer((uint32_t)(heap_list_test->next->next + sizeof(heap_t)),         (uint32_t)memory3);
    error += assert_equals_integer(size_memory_3,                                            (uint32_t)heap_list_test->next->next->size);
    error += assert_equals_integer(ALLOCATED,                                                (uint32_t)heap_list_test->next->next->allocated);
    error += assert_equals_integer(0,                                                        (uint32_t)heap_list_test->next->next->next->next);


    int size_memory_4 = 4;
    char *memory4 = memory_alloc(size_memory_4);
    heap_list_test = get_heap_list();
    error += assert_equals_integer((uint32_t)(heap_list_test->next->next->next + sizeof(heap_t)), (uint32_t)memory4);
    error += assert_equals_integer(size_memory_4,                                            (uint32_t)heap_list_test->next->next->next->size);
    error += assert_equals_integer(ALLOCATED,                                                (uint32_t)heap_list_test->next->next->next->allocated);
    error += assert_equals_integer(0,                                                        (uint32_t)heap_list_test->next->next->next->next->next);


    free(heap);

    printf("memory_test_four_alloc executed with %u errors.\n", error);
}


void memory_test_free_and_alloc(void)
{
    unsigned int error = 0;

    char *heap = (char *)malloc(1024);
    heap_t* heap_list_test = get_heap_list();

    // 1. Memory init
    memory_init(heap, 1024);


    // 2. Allocation
    memory_alloc(1);
    memory_alloc(2);
    memory_alloc(3);
    char *memory = memory_alloc(4);
    memory_alloc(5);

    //free
    heap_t *h = heap_list_test->next->next->next;
    memory_free(memory);
    error += assert_equals_integer(UNALLOCATED, (uint32_t)(h->allocated));
    memory_alloc(2);
    error += assert_equals_integer(ALLOCATED,   (uint32_t)(h->allocated));
    error += assert_equals_integer(2,           (uint32_t)(h->size));

    free(heap);

    printf("memory_test_free_and_alloc executed with %u errors.\n", error);
}


void memset_test(void)
{
    unsigned int error = 0;
#define SIZE_MEMSET_TEST 128

    char *heap = (char *)malloc(SIZE_MEMSET_TEST);
    char *p = heap;
    int i;
    for (i = 0; i < SIZE_MEMSET_TEST; i++)
    {
        *p = i;
        p++;
    }

    rpi_memset(heap, 0, SIZE_MEMSET_TEST);

    p = heap;

    for (int i = 0; i < SIZE_MEMSET_TEST; i++)
    {
        error += assert_equals_integer(0, *p);
        p++;
    }

    free(heap);
    printf("memset_test executed with %u errors.\n", error);
}


int main()
{
    printf("\n\n *** MALLOC TEST ***\n");
    memory_test_init();
    memory_test_four_alloc();
    memory_test_free_and_alloc();
    memset_test();
}
