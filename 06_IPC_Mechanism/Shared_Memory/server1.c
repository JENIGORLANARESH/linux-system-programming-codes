#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define KEY 1234
#define SIZE 1024

//server
int main(void){
	int shmid;
	char *shmptr;

	shmid = shmget(KEY, SIZE, IPC_CREAT | 0640);
	if(shmid < 0){
		perror("shmget");
		exit(1);
	}
	shmptr = (char *)shmat(shmid, NULL, 0);
	if(shmptr == (char *)-1){
		perror("shmat");
		exit(1);
	}
	
	sleep(10);
	printf("Message from client : %s\n", shmptr);

	shmdt(shmptr);
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
