#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	pid_t pid;
	pid = fork();
	if(pid == 0){
		printf("child process executing execl()\n");
		execl("/bin/ls", "ls", "-l", NULL);
		exit(0);
	}
	else{
		wait(NULL);
		printf("Parent process\n");
	}
	return 0;
}
