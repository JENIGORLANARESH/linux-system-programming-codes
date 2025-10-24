#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void watchdog_simulation(int sig){
	printf("[WATCHDOG] Timeout! Program unresponsive. Restarting system...\n");
//	_exit(1);
}

int main(void){
	signal(SIGALRM, watchdog_simulation);
//	alarm(1);
	while(1){
		alarm(3);
		printf("System running fine..Feeding watchdog\n");
		sleep(4);
	}
	return 0;
}
