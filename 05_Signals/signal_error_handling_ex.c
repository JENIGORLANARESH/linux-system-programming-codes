#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void handle_sig(int sig){
	printf("caught signal : %d..\n", sig);
}

int main(void){
	signal(SIGINT, handle_sig);
	printf("installed signal handler \n");
	printf("program is running press ctrl + c to send SIGINT signal..\n");

	while(1){
		int ret = pause();
		if(ret == -1){
			if(errno == EINTR){
				printf("pause was interrupted by a signal. errno = EINTR\n");
			}
			else{
				perror("errno");
				exit(1);
			}
		}	
	}
	return 0;
}
