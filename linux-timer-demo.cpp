#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

// The code is loosely based on the demo on the timer_create() man page of the
// Linux man-mages project. 2015-07-23.
// (C) 2017, Bernd Porr, mail@berndporr.me.uk
// License is GPL-3.0. See the LICENSE file.

#define CLOCKID CLOCK_MONOTONIC
#define SIG SIGRTMIN

// global variable to check if the callback is called
// from our timer
timer_t timerid;


#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE);	\
	} while (0)



static void handler(int sig, siginfo_t *si, void *uc ) {
	timer_t id = *((timer_t*)si->si_value.sival_ptr);
	printf("Caught signal %d,id=%lx -- ", sig,(long)id);
	if (id==timerid) {
		printf(" and it's our timer!\n");
	} else {
		printf(" and it's somebody else!\n");
	}
}


int main(int argc, char *argv[])
{
	struct sigevent sev;
	struct itimerspec its;
	long long freq_nanosecs;
	sigset_t mask;
	struct sigaction sa;

	printf("Establishing handler for signal %d\n", SIG);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIG, &sa, NULL) == -1)
		errExit("sigaction");

	
	/* Create the timer */

	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIG;
	sev.sigev_value.sival_ptr = &timerid;
	if (timer_create(CLOCKID, &sev, &timerid) == -1)
		errExit("timer_create");

	printf("timer ID is 0x%lx\n", (long) timerid);

	/* Start the timer */

	// starts instantly
	its.it_value.tv_sec = 0;
	its.it_value.tv_nsec = 1;

	// and fires every 500ms
	its.it_interval.tv_sec = 0;
	its.it_interval.tv_nsec = 500000000;

	if (timer_settime(timerid, 0, &its, NULL) == -1)
                errExit("timer_settime");

	while (1) sleep(10);

	exit(EXIT_SUCCESS);
}
