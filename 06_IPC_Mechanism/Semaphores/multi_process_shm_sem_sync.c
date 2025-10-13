#include <stdio.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define SEMKEY 123
#define SHMKEY 345
#define SIZE 100
#define PROCESSES 3

struct sembuf Wait = {0, -1, 0};
struct sembuf Signal = {0, 1, 0};

int main(void){
	int semid, shmid;
	char *shmptr;
	pid_t pid;

	shmid = shmget(SHMKEY, SIZE, IPC_CREAT | 0666);
	shmptr = shmat(shmid, NULL, 0);

	semid = semget(SEMKEY, 1, IPC_CREAT | 0666);
	semctl(semid, 0, SETVAL, 1);
	char msg[SIZE];

	for(int i=0; i<PROCESSES; i++){
		pid = fork();
		if(pid == 0){
			semop(semid, &Wait, 1);
			printf("Process : %d writing to shared memory \n", i+1);
			printf("Enter : ");
			fgets(msg, SIZE, stdin);
			msg[strcspn(msg, "\n")] = '\0';
			memcpy(shmptr, msg, strlen(msg)+1);
			printf("Process : %d wrote -> %s\n",i+1,  shmptr);
			semop(semid, &Signal, 1);
			sleep(1);
			shmdt(shmptr);
			exit(0);
		}
	}

	for(int i=0; i<PROCESSES; i++){
		wait(NULL);
	}

	printf("Final shmptr = %s\n", shmptr);

	shmdt(shmptr);
	shmctl(shmid, IPC_RMID, NULL);
	semctl(semid, 0, IPC_RMID);
	
	return 0;
}

