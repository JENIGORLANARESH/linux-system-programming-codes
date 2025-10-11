#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>

#define KEY 1234
#define SIZE 100

int main(void){
	int shmid;
	char *shmptr;

	shmid = shmget(KEY, SIZE, IPC_CREAT | 0666);
	if(shmid < 0){
		perror("shmget");
		exit(1);
	}
	printf("shared memeory created\n");
	shmptr = (char *)shmat(shmid, NULL, 0);
	
	printf("shared memory address : %p\n", shmptr);

	strcpy(shmptr, "Hello world");

	printf("Data copied to shmptr : %s\n", shmptr);

	shmdt(shmptr);
	shmctl(shmid, IPC_RMID, NULL);
	printf("shared memory datached\n");

	return 0;
}
