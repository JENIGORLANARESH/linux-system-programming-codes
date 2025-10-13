#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

struct sembuf wait[2] = {
	{0, -1, 0},
	{1, -1, 0}
};
struct sembuf signal[2] = {
	{0, 1, 0},
	{1, 1, 0}
};

int main(void){
	int semid;
	key_t key;
	int nosems = 2;	// 2 binary semaphores

	key = IPC_PRIVATE;
	//key = ftok("file", 'A');
	if(key == -1){
		perror("ftok");
		exit(1);
	}

	semid = semget(key, nosems, IPC_CREAT | 0666);
	if(semid < 0){
		perror("semget");
		exit(1);
	}

	unsigned short values[2] = {1,1};
	union semun arg;
	arg.array = values;

	int ret = semctl(semid, 0, SETALL, arg);
	if(ret == -1){
		perror("semctl SETALL");
		exit(1);
	}

	printf("Initialized %d binary semaphores with value 1\n", nosems);

	printf("Performing wait operation\n");

	ret = semop(semid, wait, 2);
	if(ret == -1){
		perror("semop wait");
		exit(1);
	}

	printf("Entered critical section\n");
	
	unsigned short current_values[nosems];
	arg.array = current_values;
	
	semctl(semid, 0, GETALL, arg);
	printf("\nsemaphore values before signal\n");
	for(int i=0; i<nosems; i++){
		printf("Semaphore %d = %d\n", i, current_values[i]);
	}

	sleep(3);
	printf("Performing signal operation\n");
	
	ret = semop(semid, signal, 2);
	if(ret == -1){
		perror("semop signal");
		exit(1);
	}

	printf("Exiting critical section\n");

	semctl(semid, 0, GETALL, arg);
	printf("\nsemaphore values after signal\n");
	for(int i=0; i<nosems; i++){
		printf("Semaphore %d = %d\n", i, current_values[i]);
	}

	semctl(semid, 0, IPC_RMID);

	printf("\nSemaphore set removed\n");

	return 0;
}

