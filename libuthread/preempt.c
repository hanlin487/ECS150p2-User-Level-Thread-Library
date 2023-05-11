#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100
#define UNUSED(x) (void)(x)
struct sigaction old_action;
struct itimerval old_timer;

void handler(int signum){
	UNUSED(signum);
	uthread_yield();
}

void preempt_disable(void)
{
	/* TODO Phase 4 */
}

void preempt_enable(void)
{
	/* TODO Phase 4 */
}

void preempt_start(bool preempt)
{
	/* TODO Phase 4 */
	if (preempt){
		// signal handler setup
		struct new_action sighandler;
		new_action.sa_handler = handler;
		sigemptyset(&new_action.sa_mask);
		new_action.sa_flags = 0;
		sigaction(SIGVTALRM, &new_action, &old_action);

		// alarm setup
		struct itimerval new_timer;
		new_timer.it_value.tv_usec = 100 * HZ;
		new_timer.it_value.tv_sec = 0;
		new_timer.it_interval.tv_usec = 100 * HZ;
		new_timer.it_interval.tv_sec = 0;
		setitmer(ITIMER_VIRTUAL, &new_timer, &old_timer);

	}
}

void preempt_stop(void)
{
	/* TODO Phase 4 */
}

