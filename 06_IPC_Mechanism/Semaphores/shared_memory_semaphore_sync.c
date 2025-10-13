#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHMKEY 123
#define SEMKEY 345
#define SIZE 1000

union semun{
	int val;
	struct semid_ds *bf;
	unsigned short *array;
};

void sem_wait(int semid, int semnum){
	struct sembuf op = {semnum, -1, 0};
	semop(semid, &op, 1);
}
void sem_signal(int semid, int semnum){
	struct sembuf op = {semnum, 1, 0};
	semop(semid, &op, 1);
}

int main(void){
	int shmid, semid;
	char *shmptr;
	pid_t pid;

	shmid = shmget(SHMKEY, SIZE, IPC_CREAT | 0666);
	shmptr = (char *)shmat(shmid, NULL, 0);

	semid = semget(SEMKEY, 2, IPC_CREAT | 0666);
	union semun arg;
	unsigned short values[2] = {1, 0};
	arg.array = values;
	semctl(semid, 0, SETALL, arg);

	printf("Shared memory and semaphore initialized\n");

	pid = fork();
	if(pid == 0){	//child = consumer
		for(int i=0; i<5; i++){
			sem_wait(semid, 1);
			printf("consumer : shared memory : %s\n", shmptr);
			sem_signal(semid, 0);
			sleep(1);
		}
		shmdt(shmptr);
		exit(0);
	}
	else{	//parent = producer
		for(int i=0; i<5; i++){
			sem_wait(semid, 0);
			snprintf(shmptr, SIZE, "Message %d from producer\n", i+1);
			printf("Producer : wrote to shmptr : %s\n", shmptr);
			sem_signal(semid, 1);
			sleep(1);
		}

		wait(NULL);

		shmdt(shmptr);
		shmctl(shmid, IPC_RMID, NULL);
		semctl(semid, 0, IPC_RMID);
	}

	return 0;
}
