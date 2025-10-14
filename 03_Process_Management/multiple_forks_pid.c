#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	pid_t pid;

	for(int i=0; i<5; i++){
		pid = fork();
		if(pid < 0){
			perror("fork");
			exit(1);
		}
		else if(pid == 0){
			printf("child pid = %d , ppid = %d \n", getpid(), getppid());
			exit(0);
		}
	}
	for(int i=0; i<5; i++){
		wait(NULL);
	}

	printf("Parent pid = %d , ppid = %d\n", getpid(), getppid());
	return 0;
}
