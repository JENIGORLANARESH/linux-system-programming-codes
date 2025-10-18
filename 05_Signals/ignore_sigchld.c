#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void signal_handler(int sig){
	int status;
	pid_t pid = waitpid(-1, &status, WNOHANG);
	if(pid > 0){
		printf("Handled SIGCHLD : child %d terminated\n", pid);
	}
	// Note: children that already exited while SIGCHLD was ignored will not cause the handler to run now — they were already auto-reaped by the kernel while ignored.
}

int main(void){
	struct sigaction sa;
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	
	sigaction(SIGCHLD, &sa, NULL);

	printf("Parent PID : %d\n" , getpid());

	pid_t pid = fork();
	
	if(pid == 0){
		printf("child process PID : %d is running \n", getpid());
		sleep(2);
		printf("child is exiting\n");
		exit(0);
	}
	else{
		printf("parent temporarily ingores child for 5 seconds\n");
		signal(SIGCHLD, SIG_IGN);
		sleep(5);

		printf("Parent restoring : SIGCHLD handler\n");
		sigaction(SIGCHLD, &sa, NULL);

//		sleep(5);

		printf("Parent : Done\n");
	}
	return 0;
}
