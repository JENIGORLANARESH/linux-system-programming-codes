#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void){
	key_t key;
	int msgid;
	printf("Enter message key : ");
	scanf("%i", &key);
	
	msgid = msgget(key, 0640);
	if(msgid < 0){
		perror("msgget");
		printf("message queue with key %d not found\n", key);
		exit(1);
	}

	printf("Message queue with key %d found\n", key);

	char ch;
	printf("Do you want to delete? Y or N : ");
	scanf(" %c", &ch);

	if(ch == 'y' || ch == 'Y'){
		msgctl(msgid, IPC_RMID, NULL);
		printf("Message queue successfully removed\n");
	}
	else{
		printf("Delettion cancelled\n");
	}

	return 0;
}
