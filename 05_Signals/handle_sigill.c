#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigill_handler(int sig){
	printf("caught signal %d (SIGILL)\n", sig);
	printf("exiting\n");
	_exit(0);
}

int main(void){
	struct sigaction sa;
	sa.sa_handler = sigill_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	int ret = sigaction(SIGILL, &sa, NULL);
	if(ret == -1){
		perror("sigaction");
		exit(1);
	}

	printf("installed customed sigill handler\n");
	printf("intentionally raising sigill raise()\n");

	raise(SIGILL);

	printf("this line will never execute\n");

	return 0;
}
