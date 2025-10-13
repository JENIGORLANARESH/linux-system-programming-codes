#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SIZE 100
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

//chat 2
int main(void){
	mkfifo(FIFO1 , 0666);
	mkfifo(FIFO2, 0666);

	int fd_read = open(FIFO1, O_RDONLY);
	int fd_write = open(FIFO2, O_WRONLY);
	char msg[SIZE];

	while(1){
		read(fd_read, msg, SIZE);
		printf("A : %s\n", msg);	
		if(strcmp(msg, "exit") == 0){
			break;
		}
		printf("B : ");
		fflush(stdout);
		fgets(msg, SIZE, stdin);
		msg[strcspn(msg, "\n")] = '\0';
		write(fd_write, msg, SIZE);
		if(strcmp(msg, "exit") == 0){
			break;
		}
	}

	close(fd_read);
	close(fd_write);

	return 0;
}
