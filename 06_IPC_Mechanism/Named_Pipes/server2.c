#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define FIFO "fifo_name"
#define SIZE 100

//server
int main(void){
	int fd_read;
	mkfifo(FIFO, 0666);
	fd_read = open(FIFO, O_RDONLY);
	char msg[SIZE];
	while(1){
		read(fd_read, msg, SIZE);
		printf("Message received : %s\n", msg);
		if(strcmp(msg, "exit") == 0){
			break;
		}
	}

	close(fd_read);
	unlink(FIFO);
	
	return 0;
}
