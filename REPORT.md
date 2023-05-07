# Project 2
## Queue Implementation
#### Queue Data Structure Design
The queue implementation is pretty simple with all the functions defined in\
the header. The actual queue structure is pretty simple as it's just a\
linked list with `node` objects that contain a `void *` data pointer and a\
`node *` pointer to the next node. As for the `queue` itself includes the\
`head`, `tail`, and `size`.  


#### Queue Functions  
- `queue_create` is made by attempting to allocate memory for the queue first\
 but the function, like many other functions, checks for the success of the\
 memory allocation with a function like\
&nbsp;&nbsp;&nbsp;&nbsp;`if (q == NULL){`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`return NULL;`\
&nbsp;&nbsp;&nbsp;&nbsp;`}`\
and `NULL` will be returned if the allocation fails.\
- For freeing the `queue` it requires that the `queue` have allocated memory\
and be empty, and if it's not empty then the nodes must be dequeued before\
destroying the queue via `queue_destroy`.\
- `queue_enqueue`, `queue_dequeue`, and `queue_delete` all perform their\
respective jobs with `queue_enqueue` appending nodes to the queue **tail**\
and incrementing the **size**.\
- `queue_dequeue` does the exact opposite by removing the **head** node,\
returning the data to a `void **` pointer, and updating the **head** and\
**size**.\
- `queue_delete` is pretty straightforward too, it takes in the `queue`\
object and the `data` that is to be deleted and deletes it. `queue` **size**\
and its nodes are also updated accordingly. 