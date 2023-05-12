#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "private.h"
#include "uthread.h"

struct semaphore {
	size_t count;
	queue_t waiting;
	
};

sem_t sem_create(size_t count)
{
	sem_t s = (sem_t) malloc(sizeof(sem_t));

	if (s == NULL){
		return NULL;
	}

	

	s -> count = count;
	s -> waiting = queue_create();
	return s;
}

int sem_destroy(sem_t sem)
{
	if (sem == NULL || queue_length(sem -> waiting) > 0){
		return -1;
	}

	queue_destroy(sem -> waiting);
	free(sem);
	sem = NULL;
	return 0;
}
	




int sem_down(sem_t sem)
{
	if (sem == NULL){
		return -1;
	}


	if (sem -> count > 0){
		
		sem -> count -=1;
	}
	else if(sem -> count == 0){
		struct uthread_tcb *temp_2 = uthread_current();
		queue_enqueue(sem -> waiting, (void*) temp_2);
		uthread_block();
	}
	return 0;
}

int sem_up(sem_t sem)
{
	if (sem == NULL){
		return -1;
	}

	if (sem -> count == 0){
		if (queue_length(sem -> waiting) > 0){
			struct uthread_tcb *first_in_line;
			queue_dequeue(sem -> waiting, (void**)&first_in_line);
			uthread_unblock(first_in_line); 

		}

		else{
			sem -> count += 1;
		}
	}

	else if(sem -> count > 0){
		sem -> count += 1;
	}

	return 0;

	
}

