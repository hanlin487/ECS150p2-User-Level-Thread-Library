#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "queue.h"

typedef struct node {
	void* data;
	struct node* next;

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
	queue_t q = (queue_t) malloc(sizeof(queue));

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

	/* if queue empty then node = head = tail 
		else just append it */
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
	/* if queue or data are null or queue is empty return -1 */
	if (queue == NULL || data == NULL || queue->size == 0){
		return -1;
	}

	node* old_node = queue->head;
	*data = queue->head->data;
	queue->head = queue->head->next;

	free(old_node);
	queue->size--;
	return 0;
}

int queue_delete(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	if (queue == NULL || data == NULL){
		return -1;
	}

	/* if only one node and node data matches */
	if (queue->size == 1 && queue->head->data == data){
		free(queue->head);

		queue->head = NULL;
		queue->tail = NULL;
		queue->size--;

		return 0;
	}

	/* if queue size > 1 and queue head is a match */
	else if (queue->head->data == data){
		node* temp = queue->head;
		queue->head = queue->head->next;

		free(temp);
		queue->size--;

		return 0;
	}

	/* otherwise find the node in the queue (if it exists) */
	else {
		node* n = queue->head;
		node* temp;

		while (n != NULL){
			if (n->data == data){
				temp->next = n->next;

				free(n);
				queue->size--;
				return 0;
			}

			temp = n;
			n = n->next;
		}
	}
	return -1;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	/* TODO Phase 1 */
	if (queue == NULL || func == NULL){
		return -1;
	}

	node* n = queue->head;
	node* next_node;

	while (n != NULL){
		next_node = n->next;
		func(queue, n->data);
		n = next_node;
	}

	return 0;
}

int queue_length(queue_t queue)
{
	/* TODO Phase 1 */
	return queue->size;
}

