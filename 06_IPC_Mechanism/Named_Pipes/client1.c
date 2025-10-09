#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

//client
int main(void){
	int svfd, clfd;
	char rxbuf[100], txbuf[100];

	printf("Enter message : ");
	fgets(txbuf, sizeof(txbuf), stdin);
	txbuf[strcspn(txbuf, "\n")] = '\0';

	svfd = open("srvfifo", O_WRONLY); 
	write(svfd, txbuf, strlen(txbuf)+1);
	close(svfd);

	printf("Waiting for reply from server\n");
	clfd = open("clfifo", O_RDONLY);
	read(clfd, rxbuf, sizeof(rxbuf));
	printf("Received : %s\n", rxbuf);

	close(clfd);

	return 0;
}
