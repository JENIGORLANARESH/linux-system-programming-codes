#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigwinch(int sig){
	printf("Caught the signal %d (SIGWINCH)..\n", sig);
	printf("Window size changed..\n");
}

int main(void){
	struct sigaction sa;
	sa.sa_handler = handle_sigwinch;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	int ret = sigaction(SIGWINCH, &sa, NULL);
	if(ret == -1){
		perror("sigaction");
		exit(1);
	}

	while(1){
		//pause();
	}

	return 0;
}
