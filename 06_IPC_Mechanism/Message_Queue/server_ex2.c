#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define KEY 1234
#define TYPE 1

//server
int main(void){
	int msgid;
	char rxbuf[50];
	char txbuf[50];

	msgid = msgget(KEY, IPC_CREAT | 0640);

	printf("Waiting for client message : \n");
	
	msgrcv(msgid, rxbuf, 50, TYPE, 0);
	
	printf("%s\n", rxbuf+16);

	memcpy(txbuf, rxbuf+8, 8);
	printf("Enter message : \n");
	scanf("%s", txbuf+8);

	msgsnd(msgid, txbuf, 8+strlen(txbuf), 0);

	printf("message sent\n");

	msgctl(msgid, IPC_RMID, NULL);


	return 0;
}
