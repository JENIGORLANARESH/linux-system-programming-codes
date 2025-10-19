#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>

void handle_sigxfsz(int sig){
	printf("Cuaght the siganl %d (SIGXFSZ).\n", sig);
	printf("File size exceeded\n");
	printf("exiting program.\n");
	_exit(0);
}

int main(void){
	struct sigaction sa;
	struct rlimit limit;
	FILE *fp;

	sa.sa_handler = handle_sigxfsz;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGXFSZ, &sa, NULL);

	printf("installed sigxfsz handleer\n");

	limit.rlim_cur = 1024;
	limit.rlim_max = 1024;
	setrlimit(RLIMIT_FSIZE, &limit);

	printf("File size limit set to 1KB\n");

	fp = fopen("data.txt", "w");
	printf("writing data to file continuesly data.txt \n");
	while(1){
		fprintf(fp, "this is written to file continueosly until it reaches limit\n");
		usleep(100000);
	}

	fclose(fp);

	return 0;
}
