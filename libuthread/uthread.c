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
//static queue_t blocked_q = NULL;
static struct uthread_tcb* running;

struct uthread_tcb* createThread(void){
    uthread_tcb *u = malloc(sizeof(struct uthread_tcb));
    u->context = (uthread_ctx_t*) malloc(sizeof(uthread_ctx_t));
    u->stack_pointer = NULL;
    u->state = READY;

    return u;
}

int uthread_create(uthread_func_t func, void *arg){
    uthread_tcb *temp = createThread();

    /* precheck */
    if (temp == NULL){
        return -1;
    }

    temp->stack_pointer = uthread_ctx_alloc_stack();

    /* precheck */
    if (temp->stack_pointer == NULL){
        return -1;
    }

    uthread_ctx_init(temp->context, temp->stack_pointer, func, arg);
    queue_enqueue(ready_q, (void*) temp);
    
    return 0;
}

void uthread_yield(void){
    running->state = READY;
    queue_enqueue(ready_q, (void*) running);
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

    if (queue_dequeue(ready_q, (void**) &running) == -1){
	    free(running);
	    free(first_proc);

	    return;
    }
    else{
	    running->state = RUNNING;
	    uthread_ctx_switch(first_proc->context, running->context);
	    free(first_proc);
    }
}

int uthread_run(bool preempt, uthread_func_t func, void *arg){
    if (preempt){
	    printf("preempt");
    }

    ready_q = queue_create();

    /* precheck */
    if (ready_q == NULL){
        return -1;
    }
    //blocked_q = queue_create();

    //Turn running thread into a struct
    running = createThread();

    /* precheck */
    if (running == NULL){
        return -1;
    }

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

struct uthread_tcb *uthread_current(void){
    return running;
}

void uthread_block(void){
    running->state = BLOCKED;
    //queue_enqueue(blocked_q, (void*)running);
    uthread_tcb *first_proc;
    first_proc = running;

    //Add an empty queue case here like in exit
    queue_dequeue(ready_q, (void**) &running);
    running->state = RUNNING;
    uthread_ctx_switch(first_proc->context, running->context);
}

void uthread_unblock(struct uthread_tcb *uthread){
    uthread->state = READY;
    //queue_delete(blocked_q,(void*) uthread);
    queue_enqueue(ready_q, (void*) uthread);
}
