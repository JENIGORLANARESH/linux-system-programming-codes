#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigquit_handler(int sig){
	printf("Caught signal %d (SIGQUIT).\n", sig);
	printf("exiting.\n");
	_exit(0);
}

int main(void){
	struct sigaction sa;
	sa.sa_handler = sigquit_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	int ret = sigaction(SIGQUIT, &sa, NULL);
	if(ret == -1){
		perror("sigaction");
		exit(1);
	}

	printf("installed handler for SIGQUIT = ctrl + \\ \n");
	printf("press ctrl + \\ to raise siganl\n");

	while(1){
		printf("running\n");
		sleep(2);
	}

	return 0;
}
