#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 1234
#define MSG_SIZE 100

struct msgbuf{
	long msgtype;
	char msgtext[MSG_SIZE];
};

int main(void){
	int msgid;
	struct msgbuf message;

	msgid = msgget(MSG_KEY, IPC_CREAT | 0640);
	if(msgid == -1){
		perror("msggettt");
		exit(1);
	}

	printf("Server waiting for a message\n");

	if( msgrcv(msgid, &message, sizeof(message.msgtext), 0, 0) == -1){
		perror("msgrcv");
		exit(1);
	}

	printf("Received message : %s\n", message.msgtext);

	msgctl(msgid, IPC_RMID, NULL);

	printf("Message queue is deleted. Server exiting..\n");

	return 0;
}
