#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define FIFO "fifo_name"
#define SIZE 100

//client
int main(void){
	int fd_write;
	mkfifo(FIFO, 0666);
	fd_write = open(FIFO, O_WRONLY);
	char msg[SIZE];
	while(1){
		printf("Enter message : ");
		fgets(msg, SIZE, stdin);
		msg[strcspn(msg, "\n")] = '\0';
		write(fd_write, msg, SIZE);
		if(strcmp(msg, "exit") == 0){
			break;
		}
	}

	close(fd_write);
	return 0;
}
