#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define SEMKEY 123
#define SHMKEY 234
#define SIZE 100
// problem 73

union semun{
	int val;
	struct semid_ds *buf;
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
	char *shmptr;
	pid_t pid;

	int shmid = shmget(SHMKEY, SIZE, IPC_CREAT | 0666);
	shmptr = shmat(shmid, NULL, 0);
	strcpy(shmptr, "");

	int semid = semget(SEMKEY, 2, IPC_CREAT | 0666);
	unsigned short values[2] = {1, 0};
	union semun arg;
	arg.array = values;
	semctl(semid, 0, SETALL, arg);
	
	pid = fork();

	if(pid == 0){ //sem : 0 
		char childbuf[SIZE];
		char *child_shm = shmat(shmid, NULL, 0);

		while(1){
			sem_wait(semid, 1);
			strcpy(childbuf, child_shm);
			if(strcmp(childbuf, "") != 0)
				printf("Child received > %s\n", childbuf);

			if(strcmp(childbuf, "exit") == 0){
				break;
			}

			printf("Child : Enter message : ");
			fgets(childbuf, SIZE, stdin);
			childbuf[strcspn(childbuf, "\n")] = '\0';
			strcpy(child_shm, childbuf);
			if(strcmp(childbuf, "exit") == 0)
				break;
			sem_signal(semid, 0);
		}
		shmdt(child_shm);
		exit(0);
	}
	else{
		char message[SIZE];
		while(1){
			sem_wait(semid, 0);
			printf("Parent: Enter message : ");
			fgets(message, SIZE, stdin);
			message[strcspn(message, "\n")] = '\0';
			strcpy(shmptr, message);
			if(strcmp(message, "exit") == 0) break;
			sem_signal(semid, 1);

			sem_wait(semid, 0);
			
			if(strcmp(shmptr, "") != 0){
				printf("Parent received : %s\n", shmptr);
			}
			if(strcmp(shmptr, "exit") == 0) break;
			sem_signal(semid, 1);
		}

		wait(NULL);

		shmdt(shmptr);
		shmctl(shmid, IPC_RMID, NULL);
		semctl(semid, 0, IPC_RMID);
	}

	return 0;
}
