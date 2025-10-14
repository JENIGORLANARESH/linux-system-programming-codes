#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	pid_t pid;

	printf("Parent pid = %d, pgid = %d\n", getpid(), getpgrp());

	pid = fork();
	if(pid == 0){
		printf("Child pid = %d , pgid = %d\n", getpid(), getpgrp());
		int ret = setpgid(0, 0);
		if(ret == -1){
			perror("setpgid");
			exit(1);
		}
		printf("Child pid = %d , pgid = %d\n", getpid(), getpgrp());
		sleep(3);
		exit(0);
	}
	else{
		sleep(3);
		printf("parent pid = %d , pgid = %d\n", getpid(), getpgrp());
		wait(NULL);
	}
	return 0;
}
