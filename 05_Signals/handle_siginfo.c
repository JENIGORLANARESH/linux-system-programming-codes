#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//Linux users typically do not have SIGINFO. On Linux, programs that want a “status request from keyboard” usually emulate it using SIGUSR1.

void siginfo_handler(int sig){
	printf("Caught signal %d . (SIGINFO)..\n", sig);
}

int main(void){
	struct sigaction sa;

	sa.sa_handler = siginfo_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction( SIGUSR1, &sa, NULL);

	printf("installed handler for SIGINFO.\n");
	printf("Enter kill -SIGUSR1 %d for manual triggering.\n", getpid());
	printf("Enter ctrl + C to exit\n");
	int count = 0;
	while(1){
		count++;
		printf("running.. count : %d\n", count);
		sleep(2);
	}

	return 0;
}
