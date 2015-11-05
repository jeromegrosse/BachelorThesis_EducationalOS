#include "queue.h"
#include "types.h"
#include "constants.h"
#include "malloc.h"

queue* create_queue(void)
{
    queue* q = (queue*) memory_alloc(sizeof(queue));
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;

    return q;
}

void* dequeue(queue* q)
{
    if(q->size == 0) {
        return NULL;
    }

    node* n = q->head;

    node* node_next = n->next;

    q->head = node_next;
    if(q->head == NULL) q->tail = NULL;
    q->size = q->size - 1;

    void* element = n->element;

    memory_free(n);

    return element;
}


void enqueue(queue* q, void* element)
{
    node* n = (node*) memory_alloc(sizeof(node));

    n->element = element;
    n->next    = NULL;

    if(q->size > 0) {
        q->tail->next = n;
    } else {
        q->head = n;
    }

    q->tail       = n;
    q->size       = q->size + 1;
}
