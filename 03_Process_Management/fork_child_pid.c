#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	pid_t pid;

	pid = fork();
	if(pid < 0){
		perror("fork");
		exit(1);
	}
	else if(pid == 0){
		printf("child pid = %d , ppid = %d\n", getpid(), getppid());
		exit(0);
	}
	else{
		wait(NULL);
		printf("parent pid = %d , ppid = %d\n", getpid(), getppid());
	}
	return 0;
}
