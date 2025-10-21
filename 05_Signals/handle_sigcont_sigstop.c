#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// SIGSTOP - cannot be caught , ignored, or handled
// SIGCONT - The kernel resumes the process.  use fg in same shell or kill -SIGCONT pid

void handle_sigcont(int sig){
	printf("caught signal %d. SIGCONT..\n", sig);
}

int main(void){
	struct sigaction sa;

	sa.sa_handler = handle_sigcont;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGCONT, &sa, NULL);
	printf("installed handler for SIGCONT\n");
	printf("Enter ctrl + z to stop (SIGSTOP)\n");
	printf("Enter fg in same shell or kill -SIGCONT %d for (SIGCONT)\n", getpid());

	int count = 0;
	while(1){
		count++;
		printf("running.. count : %d\n", count);
		sleep(1);
	}

	return 0;
}
