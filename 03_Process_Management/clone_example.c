#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include <sched.h>

int shared_counter = 0;

int counter(void *arg){
	printf("child Thread : Pid = %d\n", getpid());
	for(int i=0; i<5; i++){
		shared_counter++;
		printf("child thread incremented shared counter = %d\n", shared_counter);
		sleep(1);
	}
	return 0;
//	return NULL;
}

int main(void){
	int size = 1024 * 1024;
	char *stack = malloc(size);

	pid_t pid;
	
	pid = clone(counter, stack+size, CLONE_VM | CLONE_FS | CLONE_FILES | SIGCHLD, NULL);

	if(pid == -1){
		perror("clone");
		free(stack);
		exit(0);
	}

	printf("Parent process PID : %d\n", getpid());

	for(int i=0; i<5; i++){
		shared_counter++;
		printf("parent incremented shared counter : %d\n", shared_counter);
		sleep(1);
	}

	waitpid(pid, NULL, 0);
	printf("Final shared counter : %d\n", shared_counter);
	free(stack);

	return 0;
}
