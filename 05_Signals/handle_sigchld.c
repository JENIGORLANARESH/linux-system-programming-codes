#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handle_sigchld(int sig){
	int status;
	pid_t pid;
	//printf("caught signal : %d, SIGCHLD\n", sig);
	while( (pid = waitpid(-1, &status, WNOHANG)) > 0){
		if(WIFEXITED(status)){
			printf("parent child : %d exited with status : %d\n", pid, WEXITSTATUS(status));
		}
		else if(WIFSIGNALED(status)){
			printf("parent child : %d terminated by signal : %d\n", pid, WTERMSIG(status));
		}
	}
}

int main(void){
	struct sigaction sa;
	pid_t pid;

	sa.sa_handler = handle_sigchld;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGCHLD, &sa, NULL);

	pid = fork();

	if(pid == 0){
		printf("child pid : %d, sleeping 2sec\n", getpid());
		sleep(2);
		printf("child exiting\n");
		exit(0);
	}
	else{
		printf("parent pid : %d, waiting for child : %d\n", getpid(), pid);
		while(1){
			pause();
		}
	}

	return 0;
}
