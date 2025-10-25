#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>

void handle_sigbus(int sig){
	printf("caught signal : %d, SIGBUS...\n", sig);
	exit(1);
}

int main(void){
	int fd;
	char *map;

	signal(SIGBUS, handle_sigbus);
	printf("installed handler for SIGBUS\n");

	fd = open("demo.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	write(fd, "A", 1);	// write 1 byte to file

	map = mmap(NULL, 8192, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);	//memory map 1kb of file larger than file size

	close(fd);

	printf("file mapped. now accessing invalid memory\n");

	map[4096] = 'x';

	munmap(map, 8192);
	printf("program completed successfullyy..\n");

	return 0;
}
