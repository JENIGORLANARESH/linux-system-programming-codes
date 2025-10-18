#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigsegv_handler(int sig){
	printf("Caught signal %d (SIGSEGV).\n", sig);
	printf("exiting\n");
	_exit(0);
}

int main(void){
	struct sigaction sa;
	sa.sa_handler = sigsegv_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	int ret = sigaction(SIGSEGV, &sa, NULL);
	if(ret == -1){
		perror("sigaction");
		exit(1);
	}

	printf("sigsegv handleer installed\n");
	printf("intentionally causing segmentaion fault\n");

	int *ptr = NULL;
	*ptr = 43;

	printf("This line will never execute\n");

	return 0;
}
