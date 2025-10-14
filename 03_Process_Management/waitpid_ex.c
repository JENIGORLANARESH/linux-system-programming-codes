#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	pid_t pid1, pid2;
	int stat;

	pid1 = fork();
	if(pid1 == 0){
		printf("child pid : %d running\n", getpid());
		sleep(4);
		printf("child pid : %d exiting\n", getpid());
		exit(4);
	}

	pid2 = fork();
	if(pid2 == 0){
		printf("child pid : %d running\n", getpid());
		sleep(5);
		printf("child pid : %d exiting\n", getpid());
		exit(5);
	}

	waitpid(pid1, &stat, 0);
	if(WEXITSTATUS(stat))
		printf("child 1 exited with status : %d\n", WEXITSTATUS(stat));

	waitpid(pid2, &stat, 0);
	if(WEXITSTATUS(stat))
		printf("child 2 exited with status : %d\n", WEXITSTATUS(stat));
	
	printf("Parent process : %d exiting\n", getpid());
	return 0;
}
