#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigabrt_handler(int sig){
	printf("Caught signal %d (SIGABRT)\n", sig);
	printf("exiting ..\n");
	_exit(0);
}

int main(void){
	struct sigaction sa;
	sa.sa_handler = sigabrt_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	int ret = sigaction(SIGABRT, &sa, NULL);
	if(ret == -1){
		perror("sigaction");
		exit(1);
	}

	printf("installed signal handler for SIGABRT\n");
	printf("using abort()\n");

	abort();	//SIGABRT is generated when a process calls the abort() function.

	printf("this line will never execute\n");

	return 0;
}
