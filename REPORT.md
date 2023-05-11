# Project 2

## **Queue Implementation**

### Queue Data Structure Design

The queue implementation is pretty simple with all the functions defined in  
the header. The actual queue structure is pretty simple as it's just a  
linked list with node objects that contain a `void *` data pointer and a  
`node *` pointer to the next node. As for the queue itself it includes the  
**head, tail, and size.**  

### Queue Functionality

- `queue_create()`  checks for the success of the memory allocation with a  
function like

```c
                if (q == NULL){
                    return NULL;
                }
```

and `NULL` will be returned if the allocation fails. Otherwise initialize an  
empty queue.

- `queue_destroy()` checks to see if the queue to free is valid. If not then  
return -1 otherwise free it and return 0.  
- `queue_enqueue()`, `queue_dequeue()`, and `queue_delete()` all perform their  
respective jobs with `queue_enqueue()` appending nodes to the queue **tail**  
and incrementing the **size**. All functions have pre-checks to ensure the  
queue and node are valid before enqueuing, dequeuing, or deleting.  
- `queue_iterate()` uses a while loop to call the parameter function on each  
data in the queue from **head** to **tail**. The biggest issue is that with a  
function like `queue_delete()` the iterate function will **SEGFAULT** when  
iterate tries to iterate from the freed node. In order to work around this  
another node variable is set to `current node->next` before the queue function  
is called. After the function operates on the data node there is now a pointer  
to the next node instead of a `NULL->next` **SEFFAULT** situation.  

### Queue Testing

Testing was simple with the queue. Empty queue testing, enqueuing values,  
dequeuing values and printing them out, deleting values and ensuring size and  
node order are correct, trying to delete values that aren't in the queue,  
destroying a queue that isn't empty, destroying an empty queue, iterating  
through the queue and incrementing the data in each node or printing them out,  
etc. Memory allocation errors weren't present but that may be dependent on the  
machine. Instead to kind of "cheat" the malloc failure we just defined the  
malloc(...) call to be `NULL` so that when creating a queue or node in the  
function's precheck it fails the condition and returns -1. Tests are in the  
*queue_tester.c* file.

## **Thread Implementation**  

### Thread Design  

Our thread data structure `uthread_tcb` is a pretty simple struct that has  
a `void *` stack pointer, state, and thread context. There's also a global  
`ready_q` queue to track threads that are ready and a *static* **running**  
`uthread_tcb` for the currently running thread.  

### Thread Functionality

- An additional `createThread()` function is implemented along with the  
`uthread_create()` function in order to take care of the memory allocation for  
the thread as well as it's context; the state is set to *READY* and the stack  
pointer is `NULL` on initialization.  
- `uthread_create()` function calls `createThread()` and then calls  
`uthread_ctx_alloc_stack()` to allocate memory for the initially `NULL` stack  
pointer. Then `uthread_ctx_init()` is called with the now initialized  
`uthread_tcb` variables and whatever **func** and **arg** is passed into  
`uthread_create()`. Then in order to get the library to see that there is a  
thread that is ready to run we enqueue the created thread into the `ready_q`  
queue.  
- `uthread_yield()` takes the currently running thread, sets its state from  
*RUNNING* to *READY* and queues it in `ready_q`. Then the top thread in  
`ready_q` becomes dequeued and assigned to a thread variable and becomes the  
now running thread. Lastly a call to `uthread_ctx_switch()` is made to  
resume the new running thread's execution context.
- `uthread_exit()` is pretty straightforward. Try to dequeue the oldest thread  
from the ready queue and assign it as the currently running thread. If there  
is no thread to dequeue then free the currently running thread. Otherwise  
update the newly dequeued thread's state, switch the contexts of the old  
thread with the new thread, and free the old thread.
- `uthread_run()` initializes the ready and block queue, creates a thread  
`running`, and continuously loops with checking conditions. The conditions  
check to see if the ready queue is empty or if the thread is prompted to  
yield.
- `uthread_block()` blocks the current thread setting its state to *BLOCKED*  
and dequeues the next thread in `ready_q` as the running thread. The blocked  
thread is not queued in the function but is meant to be used in *sem.c* and is  
added to the waiting list of threads.  
- `uthread_unblock()` takes a thread, sets the state to *READY* and queues it  
to `ready_q`.  
- `uthread_current()` is added for use in *sem.c* when adding the currently  
running thread to the waiting list and simply returns the running thread.  

### Thread Testing

Thread testing was just done with the included thread tester programs and both  
passed with no erros.  

## **Semaphore Implementation**

### Semaphore Design

The semaphore structure is pretty simple in that the semaphore struct contains  
a **count** and a **waiting** `queue`. The count is used to keep track of  
whether the resource is availabe or not for threads to use and the **waiting**  
queue is the list of threads that are waiting for a semaphore to become  
available to grab.

### Semaphore Functionality

Lots of the semaphore functions make calls to functions in *uthread.c* or  
*queue.c* in order to implement the correct functionality.

- `sem_create()` takes argument **count** and allocates and initializes a new  
semaphore with count **count**.  
- `sem_destroy()` checks to make sure the semaphore exists and the waiting list  
is empty then destroys the waiting list and the semaphore after.  
- `sem_down()` will decrement **count** of the current semaphore by 1 if the  
**count** > 0 else call `uthread_current` to get the *RUNNING* thread and adds  
it to the waiting list and blocks it.  
- `sem_up()` will check if **count** is 0 and dequeue the oldest thread in the  
waiting list if the waiting list is not empty. Otherwise increment the count  
if the count is > 0 or the waiting list is empty.  

### Semaphore Testing

Semaphore testing is done with the included testing programs in the `apps`  
library.  
