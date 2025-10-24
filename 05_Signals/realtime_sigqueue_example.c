#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handle_sigrtmin(int sig, siginfo_t *info, void *context){
	printf("child : caught signal : %d\n", sig);
	printf("child : data received = %d\n", info->si_value.sival_int);
}

int main(void){
	struct sigaction sa;
	sa.sa_sigaction = handle_sigrtmin;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGRTMIN, &sa, NULL);
	
	pid_t pid;
	pid = fork();

	if(pid == 0){
		printf("child waiting : pid : %d\n", getpid());
		pause();
	}
	else{
		sleep(1);
		
		union sigval val;
		val.sival_int = 1234;
		printf("sending signal SIGRMIN, data : %d to child PID %d\n",val.sival_int, pid);
		
		sigqueue(pid, SIGRTMIN, val);

		wait(NULL);
	}

	return 0;
}
