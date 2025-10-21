#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sig(int sig){
	printf("caught signal : %d\n", sig);
}

int main(void){
	struct sigaction sa;

	sa.sa_handler = handle_sig;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGINT, &sa, NULL);

	printf("installed signal handler for SIGINT\n");
	printf("process is goint into pause(). waits until a signal is sent\n");
	pause();
	return 0;
}
