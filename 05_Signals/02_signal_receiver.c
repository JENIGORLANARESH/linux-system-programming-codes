#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int sig){
	printf("Received custom signal : SIGUSR1 (SIGNAL NO : %d)\n", sig);
}

int main(void){
	signal(SIGUSR1, signal_handler);
	printf("receiver running\n");
	printf("receiver pid = %d\n", getpid());
	while(1){
		printf("receiver running\n");
		sleep(1);
	}
	return 0;
}
