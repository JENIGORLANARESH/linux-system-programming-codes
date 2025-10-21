#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void){
	pid_t pid;
	int data;
	printf("Enter data : ");
	scanf("%d", &data);
	printf("Enter PID of process data & signal to be sent : ");
	scanf("%d", &pid);

	printf("sending SIGRTMIN to %d , along with data : %d\n", pid, data);

	union sigval sa;
	sa.sival_int = data;

	sigqueue(pid, SIGRTMIN, sa);
	printf("sent signal\n");

	return 0;
}
