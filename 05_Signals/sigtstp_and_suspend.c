#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handle_sigtstp(int sig){
	printf("caught signal : %d\n", sig);
	//fflush(stdout);
	printf("enter fg to resume..\n");
	raise(SIGSTOP);
}

int main(void){
	struct sigaction sa;
	sa.sa_handler = handle_sigtstp;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGTSTP, &sa, NULL);

	printf("installed sig hanlder for SIGTSTP\n");
	int count = 0;
	while(1){
		count++;
		printf("running.. count = %d\n", count);
		sleep(1);
	}
	return 0;
}
