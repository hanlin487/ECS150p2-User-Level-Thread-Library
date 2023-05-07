#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"
#include "queue.h"
#include "private.h"

#define READY 0
#define RUNNING 1
#define BLOCKED 2

typedef struct uthread_tcb {
    void* stack_pointer;
    int state;
    uthread_ctx_t* context;
} uthread_tcb;

static queue_t ready_q = NULL;
static queue_t blocked_q = NULL;
static struct uthread_tcb* running;

struct uthread_tcb* createThread(void){
    uthread_tcb *u = malloc(sizeof(struct uthread_tcb));
    u->context = (uthread_ctx_t*) malloc(sizeof(uthread_ctx_t));

    //You probably have to allocate memory for the context shit
    u->stack_pointer = NULL;
    u->state = READY;

    return u;
}

int uthread_create(uthread_func_t func, void *arg){
    uthread_tcb *temp = createThread();
    temp->stack_pointer = uthread_ctx_alloc_stack();
    uthread_ctx_init(temp->context, temp->stack_pointer, func, arg);
    queue_enqueue(ready_q, (void*) temp);
    
    return 0;
}

void uthread_yield(void){
    running->state = READY;
    queue_enqueue(ready_q, (void*)running);
    uthread_tcb *first_proc;
    first_proc = running;

    //Add an empty queue case here like in exit
    queue_dequeue(ready_q, (void**) &running);
    running->state = RUNNING;
    uthread_ctx_switch(first_proc->context, running->context);
}

void uthread_exit(void){
    struct uthread_tcb *first_proc;
    first_proc = running;

    if (queue_dequeue(ready_q,(void**)&running) == -1){
	    free(running);
	    free(first_proc);

	    return;
    }
    else{
	    running -> state = RUNNING;
	    uthread_ctx_switch(first_proc->context, running->context);
	    free(first_proc);
    }
}

int uthread_run(bool preempt, uthread_func_t func, void *arg){
    if (preempt){
	    printf("preempt");
    }

    ready_q = queue_create();
    blocked_q = queue_create();

    //Turn running thread into a struct
    running = createThread();
    running->state = RUNNING;
    uthread_create(func, arg);

    while (1){
	    if (queue_length(ready_q) == 0){
	        break;
        }
        else{
            uthread_yield();
        }
    }

    return 0;
}