#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

//SIGIO is sent to a process when I/O is possible on a file descriptor

void handle_sigio(int sig){
	printf("Caught signal %d. (SIGIO).\n", sig);
	printf("exxitng safely\n");
	_exit(0);
}

int main(void){
	struct sigaction sa;

	sa.sa_handler = handle_sigio;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGIO, &sa, NULL);

	printf("instaled handler for SIGIO\n");
	printf("Enter kill -SIGIO %d for manual triggering\n", getpid());


	fcntl(0 , F_SETOWN, getpid());
	fcntl(0, F_SETFL, O_ASYNC);

	printf("waiting for keyboard input...\n");

	while(1){
		pause();
	}

	return 0;
}
