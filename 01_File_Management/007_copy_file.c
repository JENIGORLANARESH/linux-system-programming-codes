#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	// read write close
#include <fcntl.h>	// open

int main(void){
	char filename[50];
	char copy[50];
	char line[1024];

	int bytesRead, bytesWrite;

	printf("Enter file to be copied : ");
	scanf("%49s", filename);
	printf("Enter copy file : ");
	scanf("%49s", copy);

	int fd1, fd2;

	fd1 = open(filename, O_RDONLY);
	
	if(fd1 == -1){
		perror(filename);
		exit(1);
	}

	fd2 = open(copy, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if(fd2 == -1){
		perror(copy);
		exit(1);
	}

	while( (bytesRead = read(fd1, line, 1024)) > 0){
		bytesWrite = write(fd2, line, bytesRead);
		if(bytesRead != bytesWrite){
			perror("Error in writing");
			close(fd1);
			close(fd2);
			exit(1);
		}
	}

	if(bytesRead == -1){
		perror("Error in reading");
	}

	close(fd1);
	close(fd2);

	printf("File copied succussfully from %s : %s\n", filename, copy);

	return 0;
}
