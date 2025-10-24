#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigurg(int sig){
	printf("caught signal : %d, SIGURG\n", sig);
}

int main(void){
	struct sigaction sa;

	sa.sa_handler = handle_sigurg;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGURG, &sa, NULL);

	printf("installed handler for SIGURG \n");
	printf("Enter kill -SIGURG %d\n", getpid());

	pause();
	return 0;
}
