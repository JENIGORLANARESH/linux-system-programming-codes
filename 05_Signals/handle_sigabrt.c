#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigabrt(int sig){
	printf("caught signal %d (SIGABRT)\n", sig);
	printf("exiting..\n");
	_exit(0);
}

int main(void){
	struct sigaction sa;

	sa.sa_handler = handle_sigabrt;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGABRT, &sa, NULL);

	printf("installed sig handler for SIGABRT \n");
	printf("triggeriing abort() after 3 sec\n");

	sleep(3);

	abort();

	return 0;
}
