#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void){
	int fd, ch;
	char filename[50];
	printf("Enter filename : ");
	scanf("%s", filename);

	fd = open(filename, O_RDONLY);
	if(fd == -1){
		perror("Error in opening file");
		exit(1);
	}

	while( read(fd, &ch, 1) != 0){
		printf("%c", ch);
	}
	
	printf("\n");
	close(fd);

	return 0;
}
