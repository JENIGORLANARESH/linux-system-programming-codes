#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void){

	int fd1[2], fd2[2];
	pid_t pid;
	char buf[50];

	if( pipe(fd1) || pipe(fd2)){
		perror("pipe");
		exit(1);
	}

	pid = fork();
	if(pid < 0){
		perror("pid");
		exit(1);
	}

	if(pid == 0){
		close(fd1[1]);
		close(fd2[0]);
		read(fd1[0], buf, sizeof(buf));
		printf("child received : %s\n", buf);
		sleep(3);
		char msg[] =  "Hello from child";
		write(fd2[1], msg, strlen(msg)+1);
		close(fd1[0]);
		close(fd2[1]);
	}
	else{
		close(fd1[0]);
		close(fd2[1]);
		char msg[] = "hello from parent";
		write(fd1[1], msg, strlen(msg)+1);
		sleep(3);
		read(fd2[0], buf, sizeof(buf));
		printf("Parent recevied : %s\n", buf);
		close(fd1[1]);
		close(fd2[0]);
	}
	return 0;
}
