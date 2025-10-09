#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	int stat;
	int pid;
	pid = fork();
	if(pid == 0){
		sleep(3);
		printf("Child Process\n");
		exit(5);
	}
	else{
		printf("Parent process\n");
	}
	wait(&stat);
	printf("%d\n", WEXITSTATUS(stat));
}
