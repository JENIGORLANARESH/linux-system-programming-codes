#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigrtmin_handler(int sig, siginfo_t *info, void *contex){
	printf("Caught signal %d. (SIGRTMIN). \n", sig);
	printf("signal pid : %d\n", info->si_pid);
	printf("signal value : %d\n", info->si_value.sival_int);
}

int main(void){
	struct sigaction sa;

	sa.sa_sigaction = sigrtmin_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGRTMIN, &sa, NULL);

	printf("installed handler for SIGRTMIN.\n");
	printf("Enter kill -SIGRTMIN %d to trigger siganl\n", getpid());

	int count = 0;
	while(1){
		count++;
		printf("running.. count : %d\n", count);
		sleep(2);
	}
	
	return 0;
}
