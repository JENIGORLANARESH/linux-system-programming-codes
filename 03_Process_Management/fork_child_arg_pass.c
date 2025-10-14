#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	char *args[] = {"Hello", "World", NULL};
	pid_t pid;

	pid = fork();
	if(pid == 0){
		printf("child pid : %d\n", getpid());
		printf("Index\tArgument\n");
		for(int i=0; i<3; i++){
			printf("%d\t%s\n", i, args[i]);
		}
		exit(0);
	}
	else{
		wait(NULL);
		printf("Parent pid : %d\n", getpid());
		printf("Parent exiting\n");
	}
	return 0;
}
