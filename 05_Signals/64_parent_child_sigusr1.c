#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

pid_t child_pid;

void parent_handle_sigusr1(int sig){
	printf("Parent received SIGUSR1\n");
	if(child_pid > 0){
		printf("parent forwarding SIGUSR1 to child : %d\n", child_pid);
		kill(child_pid, SIGUSR1);
	}
}

void child_handle_sigusr1(int sig){
	printf("child received SIGUSR1 from parent\n");
}

int main(void){
	struct sigaction parent_sa, child_sa;

	child_pid = fork();

	if(child_pid == 0){
		child_sa.sa_handler = child_handle_sigusr1;
		sigemptyset(&child_sa.sa_mask);
		child_sa.sa_flags = 0;

		sigaction(SIGUSR1, &child_sa, NULL);
		printf("child : %d waiting for SIGUSR1\n", child_pid);
		while(1){
			pause();
		}
	}
	else{
		parent_sa.sa_handler = parent_handle_sigusr1;
		sigemptyset(&parent_sa.sa_mask);
		parent_sa.sa_flags = 0;
		sigaction(SIGUSR1, &parent_sa, NULL);

		printf("parent : %d, child : %d, \n", getpid(), child_pid);
		printf("parent waiting for SIGUSR1\n");
		while(1){
			pause();
		}	
	}

	return 0;
}
