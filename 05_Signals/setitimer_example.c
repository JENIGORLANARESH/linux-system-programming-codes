#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void handle_signal(int sig){
	printf("Caught signal : %d , (SIGALRM)\n", sig);
}

int main(void){
	struct sigaction sa;
	struct itimerval timer;
	
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGALRM, &sa, NULL);

	printf("installed handler for SIGALRM.\n");

	timer.it_value.tv_sec = 1;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = 1;
	timer.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL, &timer, NULL);

	while(1){
		pause();
	}	
	
	return 0;
}
