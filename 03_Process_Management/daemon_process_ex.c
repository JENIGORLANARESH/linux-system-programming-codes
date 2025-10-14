#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	pid_t pid;
	pid = fork();
	if(pid > 0){
		printf("parent exiting , child will run as daemon process\n");
		exit(0);
	}

	setsid();

	chdir("/");

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	while(1){
		FILE *fp = fopen("/tmp/daemon_log.txt", "a");
		if(fp){
			fprintf(fp, "Daemon is running with pid %d\n", getpid());
			fclose(fp);
		}
		sleep(10);
	}

	return 0;
}
