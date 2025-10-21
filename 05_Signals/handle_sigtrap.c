#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigtrap(int sig){
	printf("Caught signal : %d, Breakpoint trap detected\n", sig);
}

int main(void){
	struct sigaction sa;
	sa.sa_handler = handle_sigtrap;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGTRAP, &sa, NULL);

	printf("installed signal handler for SIGTRAP\n");
	printf("raising SIGTRAP after 3 sec\n");
	sleep(3);
	raise(SIGTRAP);
	return 0;
}
