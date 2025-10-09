#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#define SEM_KEY 234
#define SLOTS 3

struct sembuf sem_lock = {0, -1, 0};
struct sembuf sem_unlock = {0, 1, 0};

void parking(int semid, int carid){
//	printf("Car : %d arrived and waiting..\n", carid);
	semop(semid, &sem_lock, 1);
	printf("Car : %d parked\n", carid);	
	sleep(3);
	printf("Car : %d leaving parking slot\n", carid);
	semop(semid, &sem_unlock, 1);
}

int main(void){
	int semid;
	pid_t pid;
	int no_cars = 6;

	semid = semget(SEM_KEY, 1, IPC_CREAT | 0640);
	if(semid < 0){
		perror("semid");
		exit(1);
	}
	semctl(semid, 0, SETVAL, SLOTS);

	printf("Parking slots opened with available : %d\n", SLOTS);

	for(int i=1; i<=no_cars; i++){
		pid = fork();
		if(pid == 0){
			parking(semid, i);
			exit(0);
		}
//		sleep(2);
	}

	for(int i=1; i<=no_cars; i++){
		wait(NULL);
	}

	semctl(semid, 0, IPC_RMID, 0);
	printf("All cars have left, parking lot closed\n");

	return 0;
}
