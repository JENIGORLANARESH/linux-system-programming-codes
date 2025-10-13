#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SIZE 1024
#define FIFO "fifo_name"

void *write_t(void *arg){
	int fd;
	char msg[SIZE];
	
	mkfifo(FIFO, 0666);	//make if not present
	
	while(1){	
		fd = open(FIFO, O_WRONLY);
		printf("Enter msg to read thread : ");
		fgets(msg, SIZE, stdin);
		msg[strcspn(msg, "\n")] = '\0';
		write(fd, msg, strlen(msg)+1);
		close(fd);
		if(strcmp(msg, "exit") == 0){
			break;
		}
		sleep(1);
	}
	return NULL;
}

void *read_t(void *arg){
	int fd;
	char msg[SIZE];
	
	while(1){
		fd = open(FIFO, O_RDONLY);
		read(fd, msg, SIZE);
		printf("Writer :  > %s\n", msg);
		close(fd);
		if(strcmp(msg, "exit") == 0){
			break;
		}
	}
	pthread_exit(NULL);
}

int main(void){
	pthread_t Write, Read;
	int fd;
	mkfifo(FIFO, 0666);
	
	pthread_create(&Write, NULL, write_t, NULL);
	pthread_create(&Read, NULL, read_t, NULL);

	pthread_join(Write, NULL);
	pthread_join(Read, NULL);

	unlink(FIFO);
	printf("fifo deleted\n");
	return 0;
}
