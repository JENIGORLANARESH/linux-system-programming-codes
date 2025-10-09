#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	int pid;
	pid = fork();
	if(pid == 0){
		sleep(3);
		printf("Parent pid : child ppid : %d\n", getppid());
		printf("child process.\n");
		exit(0);
	}
	else{
		printf("Parent process.\n");
		exit(0);
	}
	return 0;
}
