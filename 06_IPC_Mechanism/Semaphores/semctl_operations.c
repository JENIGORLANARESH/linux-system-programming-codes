#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEMKEY 1234

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int main(void){
	int semid;
	struct semid_ds seminfo;

	semid = semget(SEMKEY, 3, IPC_CREAT | 0666);

	printf("Semaphore set of 3 created with id : %d\n\n", semid);
	
	union semun arg;
	unsigned short values[3] = {1, 2, 3};
	arg.array = values;

	semctl(semid, 0, SETALL, arg);
	printf("Semaphore values initialized to (SETVAL): 1, 2, 3\n\n");

	unsigned short getall[3];
	arg.array = getall;
	semctl(semid, 0, GETALL, arg);
	printf("Current semaphore values (GETALL): \n");
	for(int i=0; i<3; i++){
		printf("Semaphore: %d , value : %d\n", i, getall[i]);
	}

	arg.val = 5;
	semctl(semid, 1, SETVAL, arg);
	printf("\nSETVAL of semaphore 1 value to : %d\n", arg.val);

	int val = semctl(semid, 1, GETVAL);
	printf("\nGETVAL of semaphore 1 : %d\n\n", val);

	arg.buf = &seminfo;
	semctl(semid, 0, IPC_STAT, arg);
	printf("Semaphore set information (IPC_STAT) \n");
	printf("Number of semaphores in the set : %ld\n", seminfo.sem_nsems);
	printf("Owner UID : %d\n", seminfo.sem_perm.uid);
	printf("Access permission (mode) : %o\n\n", seminfo.sem_perm.mode);

	semctl(semid, 0, IPC_RMID);
	printf("semaphore removed (IPC_RMID)\n");
	
	return 0;
}
