#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

//This signal is sent to a process to notify a power failure or power status change

void handle_sigpwr(int sig){
	printf("caught signal %d (SIGPWR).\n", sig);
	printf("exiting safely.\n");
	_exit(0);
}

int main(void){
	struct sigaction sa;

	sa.sa_handler = handle_sigpwr;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGPWR, &sa, NULL);

	printf("procerss PID : %d\n", getpid());
	printf("installed handler for SIGPWR.\n");
	printf("Use kill -SIGPWR %d to send signal\n", getpid());

	while(1){
		pause();	//wait for any signal
	}
	return 0;
}
