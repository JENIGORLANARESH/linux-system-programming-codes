#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signo){
	printf("Caught siganl no %d\n", signo);
	_exit(0);
}

int main(void){
	signal(SIGINT, signal_handler);
	printf("program is running\n");
	printf("press ctrl+c for SIGINT\n");
	while(1){
		printf("running\n");
		sleep(2);
	}
	return 0;
}
