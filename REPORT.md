# Project 2
## **Queue Implementation**
### Queue Data Structure Design
The queue implementation is pretty simple with all the functions defined in\
the header. The actual queue structure is pretty simple as it's just a\
linked list with `node` objects that contain a `void *` data pointer and a\
`node *` pointer to the next node. As for the `queue` itself includes the\
`head`, `tail`, and `size`.  

### Queue Functions  
- `queue_create()` is made by attempting to allocate memory for the queue first\
 but the function, like many other functions, checks for the success of the\
 memory allocation with a function like\
&nbsp;&nbsp;&nbsp;&nbsp;`if (q == NULL){`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`return NULL;`\
&nbsp;&nbsp;&nbsp;&nbsp;`}`\
and `NULL` will be returned if the allocation fails.
- For freeing the `queue` it requires that the `queue` have allocated memory\
and be empty, and if it's not empty then the nodes must be dequeued before\
destroying the queue via `queue_destroy`.
- `queue_enqueue`, `queue_dequeue`, and `queue_delete` all perform their\
respective jobs with `queue_enqueue` appending nodes to the queue **tail**\
and incrementing the **size**.
- `queue_dequeue` does the exact opposite by removing the **head** node,\
returning the data to a `void **` pointer, and updating the **head** and\
**size**.
- `queue_delete` is pretty straightforward too, it takes in the `queue`\
object and the `data` that is to be deleted and deletes it. `queue` **size**\
and its nodes are also updated accordingly. 
- `queue_iterate` is a more complex function since it's taking a function and\
takes in the arguments `queue_iterate(queue_t queue, queue_func_t func)`\
and `func` takes in arguments `(queue_t queue, void *data)`. The iterate\
is supposed to call the **function** on each `data` in the `queue` from\
**head** to **tail**. The biggest issue is that with a function like\
`queue_delete` the iterate function will **SEGFAULT** when the function that's\
called on deletes the nodes in the queue. For a `queue` with node\
`(1, 2, 3, 4)` if node 3 is deleted, the queue becomes `(1, 2, 4)` however in\
the iterate function it still points to node 3. But since node 3 is already\
freed it's now `NULL` and can't be accessed when the while loop reaches the\
line where it tries to do `current node = node 3->next` which will cause the\
**SEGFAULT**.\
In order to work around this in the `while` loop that iterates through all the\
nodes another `node` variable is used and is set to the next node of the\
current node before the function is called on the current node. This way there\
will be a variable that points to node 4 (in the context of the example above)\
and after the function is called and node 3 is deleted then the while loop\
sets the `current node = next node` instead of doing\
`current node = current node->next`.  

### Queue Testing
Testing was simple with the queue. Empty queue testing, enqueuing values,\
dequeuing values and printing them out, deleting values and ensuring size and\
node order are correct, trying to delete values that aren't in the queue,\
destroying a queue that isn't empty, destroying an empty queue, iterating\
through the queue and incrementing the data in each node or printing them out,\
etc. Memory allocation errors weren't present but that may be dependent on the\
machine. Instead to kind of "cheat" the malloc failure I just defined the\
malloc(...) call to be `NULL` so that when creating a `queue` or `node` in the\
function's precheck it fails the condition and returns -1.

## **Thread Implementation**  
### Thread Data Structure Design  
Our thread data structure `uthread_tcb` is a pretty simple struct that has  
a `void *` stack pointer, state, and thread context. There's also a queue for  
ready processes, blocked processes, and a thread TCB for the currently running\
thread.

### Thread Functions
- The function to create a thread is similar to how queues are created with an\
initial memory allocation however a `createThread()` function is implemented  
along with the `uthread_create()` function in order to take care of the memory 
allocation for the thread as well as it's context while the state is ready  
and the stack pointer is `NULL` on initialization.
- The actual `uthread_create()` function 