#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_handle(int sig, siginfo_t *info, void *context){
	if(sig == SIGSEGV){
		printf("Caught signal %d, SIGSEGV\n", sig);
	}
	else if(sig == SIGBUS){
		printf("Caught signal %d, SIGBUS\n", sig);
	}
	if(info){
		printf("sender PID : %d\n", info->si_pid);
		printf("fault Address : %p\n", info->si_addr);
	}
	_exit(0);
}

int main(void){
	struct sigaction sa;

	sa.sa_sigaction = sig_handle;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGBUS, &sa, NULL);

	printf("installed handlers for SIGSEGV and SIGBUS\n");

/*	printf("raising SIGSEGV signal after 3 seconds\n");
	sleep(3);

	int *ptr = NULL;
	*ptr = 43;
*/	
	printf("triggering SIGBUS signal after 3 sec\n");
	sleep(3);

	raise(SIGBUS);

	return 0;
}
