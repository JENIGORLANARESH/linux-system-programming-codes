#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

//server
int main(void){
	int svfd, clfd;
	char rxbuf[100], txbuf[100];
	mkfifo("srvfifo", 0640);
	mkfifo("clfifo", 0640);

	printf("Server waiting for message \n");
	svfd = open("srvfifo", O_RDONLY);
	read(svfd, rxbuf, sizeof(rxbuf));
	close(svfd);

	printf("Message received : %s\n", rxbuf);

	printf("Enter reply : ");
	fgets(txbuf, sizeof(txbuf), stdin);
	txbuf[strcspn(txbuf, "\n")] = '\0';

	clfd = open("clfifo", O_WRONLY);
	write(clfd, txbuf, strlen(txbuf)+1);
	close(clfd);

	printf("message sent\n");

	unlink("srvfifo");
	unlink("clfifo");


	return 0;
}
