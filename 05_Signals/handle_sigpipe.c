#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigpipe(int sig){
	printf("caught signal : %d, SIGPIPE\n", sig);
}

int main(void){
	struct sigaction sa;
	sa.sa_handler = handle_sigpipe;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGPIPE, &sa, NULL);

	int fd[2];
	pipe(fd);
	
	pid_t pid = fork();
	if(pid == 0){
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	else{
		close(fd[0]);
		sleep(1);
		printf("parent writing to child with no reader\n");
		write(fd[1], "Hello", 5);
		printf("program continues after handling SIGPIPE\n");
	}

	return 0;
}
