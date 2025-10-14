#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
// execvpe
int main(void){
	char *args[] = {"ls", "-l", NULL};
	char *evn = {NULL};

	int pid = fork();
	if(pid == 0){
		printf("child pid : %d\n", getpid());
		printf("executing execvpe()\n");
		execvpe("ls", args, evn);
		exit(0);
	}
	else{
		wait(NULL);
		printf("Parent pid : %d\n", getpid());
		printf("Parent exiting\n");
	}
	return 0;
}
