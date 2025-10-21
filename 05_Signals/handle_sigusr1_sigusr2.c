#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigusr(int sig){
	if(sig == SIGUSR1){
		printf("Caught signal %d (SIGUSR1)..\n", sig);
	}
	if(sig == SIGUSR2){
		printf("Caught signal %d (SIGUSR2)..\n", sig);
	}
	printf("exiting..\n");
	//_exit(0);
}

int main(void){
	struct sigaction sa;

	sa.sa_handler = handle_sigusr;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	printf("installed hanlder for SIGUSR1, SIGUSR2.\n");
	printf("use kill -SIGUSR1 %d OR kill -SIGUSR2 %d to trigger signals.\n", getpid(), getpid());
	
	/*int count = 0;
	while(1){
		count++;
		printf("running.. count = %d\n", count);
		sleep(1);
	}*/
	
	printf("program paused. pause()..\nwaiting for signal.\n");
	pause();
	printf("pause() returned after catching a signal.\n");


	return 0;
}
