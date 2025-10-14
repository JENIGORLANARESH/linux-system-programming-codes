#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	pid_t pid;
	pid = fork();
	if(pid == 0){
		printf("child process %d  running\n", getpid());
		printf("child process exiting\n");
		exit(0);
	}
	else{
		printf("Parent process %d runnning\n", getpid());
		sleep(15);
		printf("Parent exiting\n");
	}
	return 0;
}
