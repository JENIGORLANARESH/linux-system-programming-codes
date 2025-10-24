#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sig(int sig){
	if(sig == SIGINT){
		printf("Caught signal : %d, SIGINT\n", sig);
		printf("exiting..\n");
		_exit(0);
	}
	if(sig == SIGUSR1){
		printf("Caught signal : %d, SIGUSR1\n", sig);
	}
}

int main(void){

	printf("installed handler for SIGINT, SIGUSR1\n");

	pid_t pid;
	pid = fork();
	if(pid == 0){
		printf("child waiting for signal from parent. PID : %d\n", getpid());
		signal(SIGINT, handle_sig);
		signal(SIGUSR1, handle_sig);
		while(1){
			pause();
		}
	}
	else{
		sleep(1);
		printf("Sending SIGUSR1 signal to child\n");
		kill(pid, SIGUSR1);
		printf("sending SIGINT signal to child\n");
		kill(pid, SIGINT);
	}
	return 0;
}
