# Project 2
## Queue Implementation
#### Queue Data Structure Design
The queue implementation is pretty simple with all the functions defined in\
the header. The actual queue structure is pretty simple as it's just a\
linked list with `node` objects that contain a `void *` data pointer and a\
`node *` pointer to the next node. As for the `queue` itself includes the\
`head`, `tail`, and `size`.\
\
\
#### Queue Functions  
- `queue_create` is made by attempting to allocate memory for the queue first\
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
`current node = current node->next`.\
\
\
#### Queue Testing