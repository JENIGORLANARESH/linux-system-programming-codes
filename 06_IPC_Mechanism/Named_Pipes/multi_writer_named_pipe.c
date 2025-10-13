#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define FIFO "fifoname"
#define SIZE 100
#define PROCESSES 5

int main(void){
	pid_t pid;
	int fd, fd_read;

	mkfifo(FIFO, 0666);
	fd_read = open(FIFO, O_RDONLY | O_NONBLOCK);

	for(int i=0; i<PROCESSES; i++){
		pid = fork();
		if(pid == 0){
			fd = open(FIFO, O_WRONLY);
			char msg[SIZE];
			printf("Process : %d | Enter message : ", i+1);		
			fflush(stdout);
			fgets(msg, SIZE, stdin);
			msg[strcspn(msg, "\n")] = '\0';
			write(fd, msg, SIZE);
			close(fd);
			exit(0);		
		}
		else{
			wait(NULL);
		}
	}

	char msg[SIZE];

	for(int i=0; i<PROCESSES; i++){
		read(fd_read, msg, SIZE);
		printf("Message received : %s\n", msg);
		usleep(10000);
	}


	close(fd_read);
	unlink(FIFO);
	return 0;
}
