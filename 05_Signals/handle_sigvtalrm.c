#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void sigvtalrm_handler(int sig){
	printf("Caught signal %d (SIGVTALRM) : virtual timer expired\n", sig);	
}

int main(void){
	struct sigaction sa;
	struct itimerval timer;

	sa.sa_handler = sigvtalrm_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	int ret = sigaction(SIGVTALRM, &sa, NULL);
	if(ret == -1){
		perror("sigaction");
		exit(1);
	}

	printf("custom SIGVTALRM handler installed\n");

	timer.it_value.tv_sec = 1;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = 1;
	timer.it_interval.tv_usec = 0;

	ret = setitimer(ITIMER_VIRTUAL, &timer, NULL);
	if(ret == -1){
		perror("setitimer");
		exit(1);
	}

	printf("virtual timer started. fires for every 1 sec of cpu time\n");
	while(1){
		for(volatile int i=0; i<10000000000; i++);
	}
	return 0;
}
