#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	char *args[] = {"ls", "-l", NULL};
	pid_t pid;

	pid = fork();
	if(pid < 0){
		perror("fork");
		exit(1);
	}
	else if (pid == 0){
		printf("Child processe before execv\n");
		execvp(args[0], args);
		exit(0);
	}
	else{
		printf("Parent process waiting for child\n");
		wait(NULL);
		printf("Parent process exiting\n");
	}
	return 0;
}
