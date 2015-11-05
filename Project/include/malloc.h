#ifndef _MALLOC_H
#define _MALLOC_H

#include "types.h"

#define ALLOCATED   1
#define UNALLOCATED 0

void* heap_top;
void* heap_limit;

struct heap_t
{
    char   size;          // Size of the allocated memory chunk
    char   allocated;     // Is it currently allocated or has it been freed?
    struct heap_t *next;  // Next element in the single-link queue
};
typedef struct heap_t heap_t;

void rpi_memset(void *b, int c, unsigned int len);
void memory_init(void* heap_start_address, uint32_t heap_size);
void* memory_alloc(uint32_t size);
void memory_free(void* data);
void memory_destroy(void);
heap_t* get_heap_list(void);

#endif
