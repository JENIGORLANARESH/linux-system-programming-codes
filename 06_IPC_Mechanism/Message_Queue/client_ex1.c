#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	msgid = msgget(MSG_KEY, 0640);
	if(msgid == -1){
		perror("msgget");
		exit(1);
	}

	printf("Enter message : ");
	fgets(message.msgtext, MSG_SIZE, stdin);
	message.msgtext[strcspn(message.msgtext, "\n")] = '\0';
	message.msgtype = 1;

	if( msgsnd(msgid, &message, sizeof(message.msgtext), 0) == -1){
		perror("msgsnd");
		exit(1);
	}

	printf("Message sent successfully\n");

	return 0;
}
