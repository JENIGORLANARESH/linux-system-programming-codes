#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigrtmax(int sig, siginfo_t *info, void *context){
	printf("Caught signal %d (SIGRTMAX) \n", sig);
	if(info){
		printf("signal : %d\n", info->si_value.sival_int);
		printf("signal pid : %d\n", info->si_pid);
	}
}

int main(void){
	struct sigaction sa;

	sa.sa_sigaction = handle_sigrtmax;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGRTMAX, &sa, NULL);

	printf("installed handler for signal : %d (SIGRTMAX)\n", SIGRTMAX);

	printf("Enter kill -%d %d to trigger signal SIGRTMAX\n", SIGRTMAX, getpid());

	int count = 0;
	while(1){
		count++;
		printf("running.. count = %d\n", count);
		sleep(2);
	}

	return 0;
}
