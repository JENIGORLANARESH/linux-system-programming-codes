#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	pid_t pid;
	pid = fork();
	if(pid == 0){
		printf("child is executing execlp()\n");
		execlp("ls", "ls", "-l", NULL);
		printf("wont execute if execlp is successfull\n");
		exit(0);
	}
	else{
		wait(NULL);
		printf("Parent exiting\n");
	}
	return 0;
}
