#ifndef QUEUE_H
#define QUEUE_H

#include "types.h"

typedef struct node
{
    void* element;
    struct node* next;
} node;


typedef struct queue
{
    uint32_t size;
    node* head;
    node* tail;
} queue;

queue* create_queue(void);
void* dequeue(queue* q);
void enqueue(queue* q, void* element);

#endif
