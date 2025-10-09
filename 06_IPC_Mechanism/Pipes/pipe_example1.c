#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	pid_t pid;
	int fd[2];
	char msg[] = "Hello world";
	char buffer[50];

	if( pipe(fd) == -1){
		perror("pipe");
		return 1;
	}

	pid = fork();
	if(pid < 0){
		perror("pid");
		return 1;
	}

	if(pid == 0){
		close(fd[1]);
		read(fd[0], buffer, sizeof(buffer));
		printf("child recevied : %s\n", buffer);
		close(fd[0]);
		sleep(1);
	}
	else{
		close(fd[0]);
		printf("parent sending : %s\n", msg);
		write(fd[1], msg, strlen(msg)+1);
		close(fd[1]);
		sleep(1);
	}
	return 0;
}
