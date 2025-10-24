#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>

void handle_sigxcpu(int sig){
	printf("caught signal : %d, SIGXCPU\n", sig);
	printf("CPU TIME exceeded..\n");
	printf("exiting..\n");
	_exit(0);
}

int main(void){
	struct sigaction sa;
	struct rlimit limit;

	limit.rlim_cur = 2;
	limit.rlim_max = 3;
	setrlimit(RLIMIT_CPU, &limit);
	
	sa.sa_handler = handle_sigxcpu;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGXCPU, &sa, NULL);
	printf("successfully set cpu time limit to 2 sec\n");
	printf("installed handlers for SIGXCPU\n");
	
	printf("cosuming more than 3 sec..\n");
	while(1){
		for(volatile long i = 0; i<100000000000000; i++);
	}
	return 0;
}
