#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define KEY 1234
#define TYPE 1

//client
int main(void){
	int msgid;
	char rxbuf[50];
	char txbuf[50];

	msgid = msgget(KEY, 0);

	long *ptr = (long *)txbuf;
	ptr[0] = TYPE;
	ptr[1] = getpid();

	printf("Enter message : ");
	scanf("%s", txbuf+16);

	msgsnd( msgid, txbuf, 8 + 8 + strlen(txbuf+16), 0 );

	printf("Waiting for server message \n");

	msgrcv(msgid, rxbuf, 50, ptr[1], 0);

	printf("%s\n", rxbuf+8);

	return 0;
}
