#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

typedef struct node {
	void* data;
	node* next;

} node;

typedef struct queue {
	/* TODO Phase 1 */
	node* head;
	node* tail;
	int size;

} queue;

queue_t queue_create(void)
{
	/* TODO Phase 1 */
	queue* q = malloc(sizeof(queue));

	/* queue creation failure */
	if (q == NULL){
		return NULL;
	}

	q->head = NULL;
	q->tail = NULL;
	q->size = 0;

	return q;
}

int queue_destroy(queue_t queue)
{
	/* TODO Phase 1 */
	if (queue == NULL || queue->size != 0){
		return -1;
	}

	free(queue);
	return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	node* n = malloc(sizeof(node));

	/* if queue or data or mem allocation failure occurs then return -1 */
	if (queue == NULL || data == NULL || n == NULL){
		return -1;
	}

	n->data = data;
	n->next = NULL;

	if (queue->size == 0){
		queue->head = n;
		queue->tail = n;
	}
	else {
		queue->tail->next = n;
		queue->tail = n;
	}

	queue->size++;
	return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
	/* TODO Phase 1 */
	node* old_node = queue->head;

	/* if queue or data are null or queue is empty return -1 */
	if (queue == NULL || data == NULL || queue->size == 0){
		return -1;
	}

	*data = queue->head->data;
	queue->head = queue->head->next;

	free(old_node);
	return 0;
}

int queue_delete(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	if (queue == NULL || data == NULL){
		return -1;
	}

	
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	/* TODO Phase 1 */
}

int queue_length(queue_t queue)
{
	/* TODO Phase 1 */
	return queue->size;
}

