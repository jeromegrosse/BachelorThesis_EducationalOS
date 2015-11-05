#include "malloc.h"
#include "constants.h"
#include "types.h"

heap_t* heap_list = (heap_t *)0; //This variable is set at address 0 up to the first allocation

void rpi_memset(void *b, int c, unsigned int len)
{
    unsigned int i            = 0;
    unsigned char *p = b;
    while(i++ < len){
        *p = c;
        p++;
    }
}

// heap_size in byte
void memory_init(void* heap_start_address, uint32_t heap_size)
{
    heap_top   = (void *)heap_start_address;
    rpi_memset(heap_start_address, 0, heap_size);

    heap_limit = (void *)(heap_start_address + heap_size*sizeof(char));
}


// We apply a first fit alogrithm
void* memory_alloc(uint32_t size)
{
    heap_t *h = heap_list;
    if(h == 0) {
        heap_list = (heap_t*)heap_top;
        h         = (heap_t *)heap_top;
    } else {
        while(1)
        {
            if(h == NULL || (h->allocated == UNALLOCATED && h->size > size) || h->size == 0) break;
            h = h->next;
        }
    }


    if(h > (heap_t*)heap_limit) {
        return NULL;
    }

    h->size       = size;
    h->allocated  = ALLOCATED;
    rpi_memset(h + sizeof(heap_t), 0, size);

    if(h->next == NULL) {
        h->next       = h + sizeof(heap_t) + size;
        h->next->size = 0;
    }

    return h + sizeof(heap_t);
}

void memory_free(void* data)
{
    heap_t *h     = (heap_t *)(data) - sizeof(heap_t);
    h->allocated  = UNALLOCATED;
}

void memory_destroy(void)
{
    heap_list = (heap_t *)0;
}

heap_t* get_heap_list(void)
{
    return heap_list;
}
