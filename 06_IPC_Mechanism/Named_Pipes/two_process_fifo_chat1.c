#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SIZE 100
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

//chat 1
int main(void){
	mkfifo(FIFO1 , 0666);
	mkfifo(FIFO2, 0666);

	int fd_write = open(FIFO1, O_WRONLY);
	int fd_read = open(FIFO2, O_RDONLY);
	while(1){
		char msg[SIZE];
		printf("A : ");	
		fflush(stdout);
		fgets(msg, SIZE, stdin);
		msg[strcspn(msg, "\n")] = '\0';
		write(fd_write, msg, SIZE);

		if(strcmp(msg, "exit") == 0){
			break;
		}

		read(fd_read, msg, SIZE);
		printf("B : %s\n", msg);
		if(strcmp(msg, "exit") == 0){
			break;
		}
	}

	close(fd_read);
	close(fd_write);
	unlink(FIFO1);
	unlink(FIFO2);

	return 0;
}
