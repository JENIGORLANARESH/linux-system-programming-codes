#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alrm_handler(int sig){
	printf("Caught SIGALRM signal %d\n", sig);
}

int main(void){
	struct sigaction sa;
	sa.sa_handler = alrm_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	int ret = sigaction(SIGALRM, &sa, NULL);
	if(ret == -1){
		perror("sigaction");
		exit(1);
	}

	printf("Setting alarm for 5 sec\n");
	alarm(5);

	printf("waiting for the alarm\n");
	pause();
	printf("program completed successfully\n");

	return 0;
}
