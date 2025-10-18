#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigtstp_handler(int sig){
	printf("Caught signal %d (SIGTSTP)\n", sig);
	printf("exiting..\n");
	_exit(0);
}

// SIGTSTP = ctrl + Z

int main(void){
	struct sigaction sa;
	sa.sa_handler = sigtstp_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	int ret = sigaction(SIGTSTP, &sa, NULL);
	if(ret == -1){
		perror("sigaction\n");
		exit(0);
	}

	printf("installed signal handler for SIGTSTP\n");
	printf("press ctrl + Z to trigger signal\n");

	while(1){
		printf("running\n");
		sleep(2);
	}

	printf("this code will never execute\n");

	return 0;
}
