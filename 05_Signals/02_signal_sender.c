#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Usage : %s <PID>\n", argv[0]);
		return 1;
	}
	pid_t pid = atoi(argv[1]);
	if(kill(pid, SIGUSR1) == 0){
		printf("Sent SIGUSR1 to process %d successfully\n", pid);
	}
	else{
		perror("failed to send signal\n");
		return 1;
	}
	return 0;
}
