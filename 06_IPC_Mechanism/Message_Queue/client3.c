#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#define KEY 1234
#define SIZE 100
#define TYPE 1

int main(void){	
	int msgid;
	char rxmsg[SIZE], txmsg[SIZE];

	msgid = msgget(KEY, 0640);
	if(msgid < 0){
		perror("msgget");
		exit(1);
	}
	
	long *txptr = (long *)txmsg;
	txptr[0] = TYPE;
	txptr[1] = getpid();

	while(1){
		printf("Enter message : ");
		scanf("%s", txmsg+16);
		msgsnd(msgid, txmsg, 8+8+sizeof(txmsg+16)+1, 0);
		if(strcmp(txmsg+16, "exit") == 0){
			break;
		}

		msgrcv(msgid, rxmsg, sizeof(rxmsg), getpid(), 0);
		printf("Server > %s\n", rxmsg+8);
	}
	printf("client exiting\n");
	return 0;
}
