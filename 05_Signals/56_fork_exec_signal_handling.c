#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int sig){
	printf("caught signal : %d....\n", sig);
}

int main(void){
	pid_t pid;
	signal(SIGUSR1, handle_signal);
	printf("parent :[%d] handled SIGUSR1 signal.\n", getpid());

	pid = fork();
	if(pid == 0){
		printf("child : [%d] inherited handler from parent.\n", getpid());	
		printf("child raising SIGUSR1 before exec\n");
		raise(SIGUSR1);
		printf("child : [%d] exxecuting new program using exec()\n", getpid());
		execl("./56_exec_child", "56_exec_child", NULL);
		
		perror("execl");
		exit(1);
	}
	else{
		sleep(2);
		printf("parent raising SIGUSR1 \n");
		raise(SIGUSR1);
		sleep(2);
		printf("exiting..parent : %d\n", getpid());
	}
	return 0;
}
