#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf env;

void handle_recover_sigsegv(int sig){
	printf("caught signal : %d, SIGSEGV\n", sig);
	longjmp(env, 1);
}

int main(void){
	struct sigaction sa;
	sa.sa_handler = handle_recover_sigsegv;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGSEGV, &sa, NULL);

	printf("installed handler for SIGSEGV\n");

	if(setjmp(env) == 0){
		printf("program stated\n");
		printf("raising sigsegv.\n");
		int *ptr = NULL;
		*ptr = 123;
		printf("this line will never execute..\n");
	}
	else{
		printf("recovered from segmentation fault..\n");
	}

	return 0;
}
