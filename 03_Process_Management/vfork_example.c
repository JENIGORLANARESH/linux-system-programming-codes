#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	pid_t pid;
	int x = 10;
	printf("process pid = %d , x = %d\n", getpid(), x);
	
	pid = vfork();
	if(pid == 0){
		printf("child pid = %d , x = %d\n", getpid(), x);
		printf("modifying x in child\n");
		x = 20;
		printf("child pid = %d , x = %d\n", getpid(), x);
		_exit(0);
	}
	else{
		wait(NULL);
		printf("Parent pid = %d , x =%d\n", getpid(), x);
	}
	return 0;
}
