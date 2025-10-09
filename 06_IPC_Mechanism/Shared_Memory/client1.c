#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define KEY 1234
#define SIZE 1024

int main(void){
	int shmid;
	char *shmptr;

	shmid = shmget(KEY, SIZE, 0640);
	if(shmid < 0){
		perror("shmget");
		exit(1);
	}
	shmptr = (char *)shmat(shmid, NULL, 0);
	if(shmptr == (char *)-1){
		perror("shmat");
		exit(1);
	}

	printf("Enter message : ");
//	scanf("%s", shmptr);
	fgets(shmptr, SIZE, stdin);

	printf("Message sent\n");
	shmdt(shmptr);

	return 0;
}
