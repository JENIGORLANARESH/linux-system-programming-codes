#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int canread = 1;

void handle_sigttin_sigttou(int sig){
	if(sig == SIGTTIN){
		printf("caught signal : %d, SIGTTIN\n", sig);
		canread = 0;
	}
	if(sig == SIGTTOU)
		printf("caught signal : %d, SIGTTOU\n", sig);
}

int main(void){
	signal(SIGTTIN, handle_sigttin_sigttou);
	signal(SIGTTOU, handle_sigttin_sigttou);

	printf("installed handlers for SIGTTIN, SIGTTOU\n");
	printf("to test : \n");
	printf("run this program in background  usign : ./a.out &\n");
	printf("then bring it to background : bg\n");
	printf("it will try to read and write to terminal and trigger signals\n");

	while(1){
		printf("attempt to write to terminal\n");
		sleep(2);
		if (canread) {
            		printf("Attempting to read from terminal...\n");
            		getchar();
        	} 
		else {
            		printf("Skipping read since SIGTTIN occurred.\n");
            		sleep(2);
        	}
	}
	return 0;
}
