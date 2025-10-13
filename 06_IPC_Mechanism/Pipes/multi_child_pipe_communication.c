#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define NOCHILD 3

int main(void){
	int fds[NOCHILD][2];
	pid_t pid;

	for(int i=0; i<NOCHILD; i++){
		pipe(fds[i]);
	}

	for(int i=0; i<NOCHILD; i++){
		pid = fork();
		if(pid == 0){
			close(fds[i][0]);
			char msg[50];
			snprintf(msg, sizeof(msg), "Message from Child %d (PID=%d)", i + 1, getpid());
			write(fds[i][1], msg, sizeof(msg));
			close(fds[i][1]);
			exit(0);
		}
	}

	for(int i=0; i<NOCHILD; i++){
		close(fds[i][1]);
	}
	

	for(int i=0; i<NOCHILD; i++){
		char msg[50];
		read(fds[i][0], msg, sizeof(msg));
		printf("Parent received : %s\n", msg);
		close(fds[i][0]);
	}
	for(int i=0; i<NOCHILD; i++){
		wait(NULL);
	}

	return 0;
}
