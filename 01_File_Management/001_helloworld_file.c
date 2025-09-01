#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
	int fd;
	fd = creat("./files/helloworld.txt", 0640);
	
	if(fd == -1){
		perror("creat filed");
		return 1;
	}

	int w = write(fd, "Hello World", strlen("Hello World"));
	
	if(w == -1){
		perror("write failed");
		close(fd);
		return 1;
	}

	close(fd);
	return 0;
}
