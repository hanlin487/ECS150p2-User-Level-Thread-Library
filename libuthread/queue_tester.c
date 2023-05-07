#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "queue.h"
#include "queue.c"

void test_create(void)
{
    queue_t q;

    q = queue_create();
    assert(q != NULL);
    printf("queue freed: %d\n", queue_destroy(q));
}

void test_queue_simple(void)
{
    queue_t q;
    int data = 3, *ptr;

    q = queue_create();
    queue_enqueue(q, &data);
    queue_dequeue(q, (void**)&ptr);
    assert(ptr == &data);
    printf("queue freed: %d\n", queue_destroy(q));
}

void print_queue(void)
{
    queue_t q;
    int data = 3, *ptr;

    q = queue_create();
    queue_enqueue(q, &data);
    
    while(queue_length(q) != 0){
        printf("\nq len: %d\n", queue_length(q));
        queue_dequeue(q, (void**) &ptr);
        printf("q element: %d\n", *ptr);
    }
    printf("queue freed: %d\n", queue_destroy(q));
}

void queue_del(void)
{
    queue_t q;
    int data = 3, *ptr;

    q = queue_create();
    queue_enqueue(q, &data);

    int data2 = 5;
    queue_enqueue(q, &data2);

    int data3 = 7;
    queue_enqueue(q, &data3);
    
    int data4 = 10;
    int del_status = queue_delete(q, &data4);
    printf("del_stat: %d\n", del_status);

    while(queue_length(q) != 0){
        queue_dequeue(q, (void**) &ptr);
        printf("\nq element: %d\n", *ptr);
        printf("q len is now: %d\n", queue_length(q));
    }
    printf("queue freed: %d\n", queue_destroy(q));
}

static void iterator_inc(queue_t q, void *data)
{
    int *a = (int*)data;

    if (*a == 42)
        queue_delete(q, data);
    else
        *a += 1;
}

static void iterate_print(queue_t q, void *data){
    int *a = (int*) data;

    printf("%d ", *a);
}

void test_iterator(void)
{
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 42, 6, 7, 8, 9};
    size_t i;

    /* Initialize the queue and enqueue items */
    q = queue_create();
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);

    /* Increment every item of the queue, delete item '42' */
    printf("\nold queue: ");
    queue_iterate(q, iterate_print);
    queue_iterate(q, iterator_inc);
    assert(data[0] == 2);
    assert(queue_length(q) == 9);
    
    printf("\nnew queue: ");
    queue_iterate(q, iterate_print);
    printf("\nsucess\n");

    int *ptr;

    while(queue_length(q) != 0){
        queue_dequeue(q,(void**) &ptr);
        printf("dequeued: %d\n", *ptr);
    }
    printf("queue freed: %d\n", queue_destroy(q));
}

int main(void){
    test_create();
    test_queue_simple();
    //print_queue();
    //queue_del();
    test_iterator();

    return 0;
}