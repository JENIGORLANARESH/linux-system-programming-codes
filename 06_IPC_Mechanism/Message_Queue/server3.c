#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

#define KEY 1234
#define SIZE 100
#define TYPE 1

int main(void){
	int msgid;
	char rxmsg[SIZE], txmsg[SIZE];

	msgid = msgget(KEY, IPC_CREAT | 0640);
	if(msgid < 0){
		perror("msgget");
		exit(1);
	}
	
	printf("Server started and waiting for client message.\n");

	while(1){
		int ret = msgrcv(msgid, rxmsg, sizeof(rxmsg), TYPE, 0);
		if(ret < 0){
			perror("msgrcv");
			break;
		}

		long *temp = (long *)rxmsg;
		long client_pid = temp[1];
		char *msg = rxmsg + 16;

		if( strcmp(msg, "exit") == 0){
			printf("client:%ld requested for exit\n", client_pid);
			break;
		}

		printf("Client > %s\n", msg);
		
		char reply[SIZE];
		printf("Enter message : ");
		scanf("%s", reply);

		long *text = (long *)txmsg;
		text[0] = client_pid;
		strcpy(txmsg+8, reply);

		msgsnd(msgid, txmsg, 8+strlen(reply)+1, 0);
	}

	msgctl(msgid, IPC_RMID, NULL);
	printf("Server exited, message queue is deleted\n");
	return 0;
}
