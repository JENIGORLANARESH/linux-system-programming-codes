#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/syscall.h>

void handle_sigsys(int sig){
	printf("Caught signal %d . (SIGSYS).\n", sig);
	printf("exxiting safely\n");
	_exit(0);
}

int main(void){
	struct sigaction sa;

	sa.sa_handler = handle_sigsys;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGSYS, &sa, NULL);
	
	printf("pid : %d\n", getpid());
	printf("installed handler for SIGSYS signal.\n");

	printf("triggering a bad system call..\n");
	printf("Enter kill -SIGSYS %d\n", getpid());	
	while(1){}
	printf("this line will never execute.\n");
	return 0;
}
