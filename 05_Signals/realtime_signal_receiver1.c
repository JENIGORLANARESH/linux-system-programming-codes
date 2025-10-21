#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int sig, siginfo_t *info, void *contex){
	printf("Caught signal : %d, \n", sig);
	printf("sender PID : %d\n", info->si_pid);
	printf("received data : %d\n", info->si_value.sival_int);
}

int main(void){
	struct sigaction sa;

	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGRTMIN, &sa, NULL);
	
	printf("process PID : %d\n", getpid());
	printf("installed signal handler for SIGRTMIN\n");

	printf("Waiting for signal SIGRTMIN along with data\n");

	int count = 0;
	while(1){
		count++;
		printf("count : %d\n", count);
		sleep(2);
	}

	return 0;
}
