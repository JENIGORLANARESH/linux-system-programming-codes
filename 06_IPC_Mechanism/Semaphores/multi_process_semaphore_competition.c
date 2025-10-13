#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SEMKEY 123
#define SHMKEY 234

struct sembuf sem_wait = {0, -1, 0};
struct sembuf sem_signal = {0, 1, 0};
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
int main(void){
	int semid, shmid;
	int *counter;
	int no_processes = 5;

	semid = semget(SEMKEY, 1, IPC_CREAT | 0666);
	union semun arg;
	arg.val = 1;
	semctl(semid, 0, SETVAL, arg);

	shmid = shmget(SHMKEY, sizeof(int), IPC_CREAT | 0666);
	counter = (int *)shmat(shmid, NULL, 0);

	for(int i=0; i<no_processes; i++){
		int pid = fork();
		if(pid == 0){
			for(int i=0; i<3; i++){
				semop(semid, &sem_wait, 1);
				int temp = *counter;
				temp++;
				*counter = temp;
				printf("process %d : counter = %d\n", getpid(), *counter);
				semop(semid, &sem_signal, 1);		
				sleep(1);
			}
			exit(0);
		}
	}

	for(int i=0; i<no_processes; i++){
		wait(NULL);
	}

	shmdt(counter);
	shmctl(shmid, IPC_RMID, NULL);
	semctl(semid, 0, IPC_RMID);

	return 0;
}
