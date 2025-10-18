#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void){
	sigset_t set, oldset;

	sigemptyset(&set);

	sigaddset(&set, SIGTERM);

	int ret = sigprocmask(SIG_BLOCK, &set, &oldset);
	if(ret < 0){
		perror("sigprocmask");
		exit(1);
	}

	printf("SIGTERM is now blocked, try $kill -TERM %d to send SIGTERM signal \n", getpid());
	printf("sleeping for 5 sec\n");
	sleep(10);
	printf("Unblocking SIGTERM\n");

	sigprocmask(SIG_SETMASK, &oldset, NULL);

	printf("SIGTERM IS UNBLOCKED\n");
	printf("waiting for 10 sec\n");
	sleep(10);
	printf("Program exiting normally\n");
	return 0;
}
