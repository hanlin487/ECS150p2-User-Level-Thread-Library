#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include "private.h"
#include "uthread.h"

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100

//GLOBAL VARIABLES FOR TIMERS AND 

static struct sigaction new;
static struct sigaction old;
static struct itimerval timer;
static struct itimerval old_t;


void helper_signal(int sig){
    	(void) sig;
	uthread_yield();

}

//GLOBAL VARIABLES FOR TIMERS AND 

static struct sigaction new;
static struct sigaction old;
static struct itimerval timer;
static struct itimerval old_t;


void helper_signal(int sig){
    	(void) sig;
	uthread_yield();

}

void preempt_disable(void)
{
       sigset_t blocking;
       sigemptyset(&blocking);
       sigaddset(&blocking,SIGVTALRM);
       sigprocmask(SIG_BLOCK, &blocking,NULL);
	
}

void preempt_enable(void)
{
	sigset_t blocking2;
	sigemptyset(&blocking2);
	sigaddset(&blocking2,SIGVTALRM);
	sigprocmask(SIG_UNBLOCK,&blocking2,NULL);
}

void preempt_start(bool preempt)
{
	if (preempt){
	    	
		memset(&new, 0, sizeof(new));
		new.sa_handler = helper_signal;
		new.sa_flags = 0;
		sigemptyset(&new.sa_mask);
		//sigaddset(&new.sa_mask, SIGVTALRM); 
		
		//Timer needs to run for 1/100th of a second so we set the starting value here using seconds + ms
		timer.it_value.tv_sec = 0;
		timer.it_value.tv_usec = ((1.0 / HZ) * 1000000);
		//After signal is sent it out we reset to the same number (1/100th of a second) and start over
		timer.it_interval.tv_sec = 0;
		timer.it_interval.tv_usec = ((1.0 / HZ) * 1000000);

		//Store old timer in old_t itimerval structure, start timer
		setitimer(ITIMER_VIRTUAL,&timer,&old_t);

		//Start signal handler 
		sigaction(SIGVTALRM, &new,&old);
	}


}

void preempt_stop(void)
{
	//Assuming we use those olds to reset timer and sig handler
	sigaction(SIGVTALRM,&old,NULL);
	setitimer(SIGVTALRM,&old_t, NULL);
}

