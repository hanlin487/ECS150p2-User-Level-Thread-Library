# Project 2
## **Queue Implementation**
### Queue Data Structure Design
The queue implementation is pretty simple with all the functions defined in\
the header. The actual queue structure is pretty simple as it's just a\
linked list with node objects that contain a `void *` data pointer and a\
`node *` pointer to the next node. As for the queue itself it includes the\
**head, tail, and size.**  

### Queue Functionality
- `queue_create()`  checks for the success of the memory allocation with a\
function like\
```c
                if (q == NULL){
                    return NULL;
                }
```
and `NULL` will be returned if the allocation fails. Otherwise initialize an\
empty queue.
- `queue_destroy()` checks to see if the queue to free is valid. If not then\
return -1 otherwise free it and return 0.
- `queue_enqueue()`, `queue_dequeue()`, and `queue_delete()` all perform their\
respective jobs with `queue_enqueue()` appending nodes to the queue **tail**\
and incrementing the **size**. All functions have pre-checks to ensure the\
queue and node are valid before enqueuing, dequeuing, or deleting. 
- `queue_iterate()` is a more complex function since it takes a function and\
takes in the arguments `(queue_t queue, queue_func_t func)` with `queue_func_t`\
arguments `(queue_t queue, void *data)`. The iterate is supposed to call\
the function on each data in the queue from **head** to **tail**. The\
biggest issue is that with a function like `queue_delete()` the iterate\
function will **SEGFAULT** when the queue function that's called on deletes\
the nodes in the queue. For a queue with nodes `(1, 2, 3, 4)` if node 3 is\
deleted, the queue becomes `(1, 2, 4)` however in the iterate function it\
still points to node 3 which is now `NULL` and can't be accessed when the\
while loop reaches the line where it tries to do execute \
`current node = node 3->next` it causes the **SEGFAULT**. In order to work\
around this another node variable is used and is set to the **next** node of\
the **current** node before the function is called on the current node. This\
way there will be a variable that points to node 4 (in the context of the\
example above) and after the function is called and node 3 is deleted then the\
while loop sets the current node = next node instead of doing current node =\
current node->next.

### Queue Testing
Testing was simple with the queue. Empty queue testing, enqueuing values,\
dequeuing values and printing them out, deleting values and ensuring size and\
node order are correct, trying to delete values that aren't in the queue,\
destroying a queue that isn't empty, destroying an empty queue, iterating\
through the queue and incrementing the data in each node or printing them out,\
etc. Memory allocation errors weren't present but that may be dependent on the\
machine. Instead to kind of "cheat" the malloc failure we just defined the\
malloc(...) call to be `NULL` so that when creating a queue or node in the\
function's precheck it fails the condition and returns -1. Tests are in the\
*queue_tester.c* file.

## **Thread Implementation**  
### Thread Data Structure Design  
Our thread data structure `uthread_tcb` is a pretty simple struct that has  
a `void *` stack pointer, state, and thread context. There's also a `ready_q`\
queue for threads that are ready, a `blocked_q` queue for threads that are\
blocked, and a *static* **running** `uthread_tcb` for the currently running\
thread.

### Thread Functionality
- An additional `createThread()` function is implemented along with the\
`uthread_create()` function in order to take care of the memory allocation for\
the thread as well as it's context; the state is set to *READY* and the stack\
pointer is `NULL` on initialization.  
- `uthread_create()` function calls `createThread()` and then calls\
`uthread_ctx_alloc_stack()` to allocate memory for the initially `NULL` stack\
pointer. Then `uthread_ctx_init()` is called with the now initialized\
`uthread_tcb` variables and whatever **func** and **arg** is passed into\
`uthread_create()`. Then in order to get the library to see that there is a\
thread that is ready to run we enqueue the created thread into the `ready_q`\
queue.
- `uthread_yield()` takes the currently running thread, sets its state from\
*RUNNING* to *READY* and queues it in `ready_q`. Then the top thread in\
`ready_q` becomes dequeued and assigned to a thread variable and becomes the\
now running thread. Lastly a call to `uthread_ctx_switch()` is made to\
resume the new running thread's execution context.
- `uthread_exit()` is pretty straightforward. Try to dequeue the oldest thread\
from the ready queue and assign it as the currently running thread. If there\
is no thread to dequeue then free the currently running thread. Otherwise\
update the newly dequeued thread's state, switch the contexts of the old\
thread with the new thread, and free the old thread.
- `uthread_run()` initializes the ready and block queue, creates a thread\
`running`, and continuously loops with checking conditions. The conditions\
check to see if the ready queue is empty or if the thread is prompted to\
yield.