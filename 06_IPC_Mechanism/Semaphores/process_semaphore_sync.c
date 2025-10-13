#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

#define key 1234
#define SHMKEY 456

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

struct sembuf Wait = {0, -1, 0};
struct sembuf Signal = {0, 1, 0};

int main(void){
	int semid, shmid;
	int *shmptr;
	pid_t pid;

	shmid = shmget(SHMKEY, sizeof(int), IPC_CREAT | 0666);
	shmptr = (int *)shmat(shmid, NULL, 0);
	*shmptr = 0;

	semid = semget(key, 1, IPC_CREAT | 0666);
	union semun arg;
	arg.val = 1;
	semctl(semid, 0, SETVAL, arg);

	pid = fork();
	if(pid == 0){
		for(int i=0; i<3; i++){
			semop(semid, &Wait, 1);
			int temp = *shmptr;
			temp++;
			*shmptr = temp;
			printf("Child entered critical section \n");
			printf("counter = %d\n", *shmptr);
			printf("Child leaving critical section\n\n");
			semop(semid, &Signal, 1);
			sleep(1);
		}
		exit(0);
	}
	else{
		for(int i=0; i<3; i++){
			semop(semid, &Wait, 1);
			int temp = *shmptr;
			temp++;
			*shmptr = temp;
			printf("Parent entered critical section\n");
			printf("counter = %d\n", *shmptr);
			printf("Parent exiting critical section\n\n");
			semop(semid, &Signal, 1);
			sleep(1);
		}

		wait(NULL);
		printf("both process finished\n");
		semctl(semid, 0, IPC_RMID);
		shmdt(shmptr);
		shmctl(shmid, IPC_RMID, 0);
	}
	return 0;
}
