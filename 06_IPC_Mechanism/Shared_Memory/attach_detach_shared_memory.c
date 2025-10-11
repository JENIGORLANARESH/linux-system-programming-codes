#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 100

int main(void){
	key_t key;
	int shmid;
	char *shmptr;

	printf("Enter existing shared memroy key : ");
	scanf("%i", &key);

	shmid = shmget(key, SIZE, 0666);
	if(shmid < 0){
		perror("shmget");
		printf("shared memory with key %i not present\n", key);
		exit(1);
	}

	shmptr = (char *)shmat(shmid, NULL, 0);
	if(shmptr == (char *)-1){
		perror("shmat");
		printf("shared memory attach failed\n");
		exit(1);
	}

	printf("shared memory attached\n");
	printf("Data in shared memory : \n %s\n", shmptr);
	
	if( shmdt(shmptr) == -1){
		perror("shmdt");
		printf("detach failed\n");
		exit(1);
	}
	printf("Shared memroy succussfully detached\n");

	return 0;
}
