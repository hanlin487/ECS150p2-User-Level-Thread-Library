#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <private.h>

#include <uthread.h>

//Expected output: 
//thread2
//thread3


void thread3(void *arg){
    	(void)arg;
	printf("thread3\n");
	exit(1);
}

void thread2(void *arg){
	(void)arg;
	printf("thread2\n");
	
	uthread_create(thread3,NULL);

}


void thread1(void *arg)
{
	(void)arg;

	uthread_create(thread2, NULL);
	preempt_disable();
	preempt_enable();


		

	while (1){
	    //If the preempt timer didn't exist it would be stuck in here forever
	    //Since it yields through everything else it exits in thread3
	    
	}
	
;




}

int main(void)
{
	uthread_run(true, thread1, NULL);
	return 0;
}
