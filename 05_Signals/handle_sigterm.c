#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int sig){
	printf("Caught signal %d (SIGTERM)..\n", sig);
	printf("exiting\n");
	_exit(0);
}

int main(void){
	struct sigaction sa;
	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	int ret = sigaction(SIGTERM, &sa, NULL);
	if(ret == -1){
		perror("sigaction");
		exit(1);
	}

	printf("process PID : %d\n", getpid());
	printf("Waiting for SIGTERM signal\n");

	while(1){
		printf("running\n");
		sleep(2);
	}

	return 0;
}
