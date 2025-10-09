#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHMKEY 12
#define SEMKEY 34
#define PRINTERS 3
#define USERS 5

struct PrinterStatus{
	int printers[PRINTERS];
};

struct sembuf lock = {0, -1, 0};
struct sembuf unlock = {0, 1, 0};

void userprocess(int semid, struct PrinterStatus *ptr, int id){
	printf("User %d waiting to print\n", id);
	semop(semid, &lock, 1);

	int printerId = -1;
	for(int i=0; i<PRINTERS; i++){
		if( ptr->printers[i] == 0){
			ptr->printers[i] = 1;
			printerId = i;
			break;
		}
	}
	printf("User %d  using printer %d\n", id, printerId+1);
	sleep(2);
	printf("User %d finished printing on printer %d\n", id, printerId+1);
	ptr->printers[printerId] = 0;
	semop(semid, &unlock, 1);
}

int main(void){
	int semid;
	int shmid;
	pid_t pid;
	struct PrinterStatus *ptrs;

	shmid = shmget(SHMKEY, sizeof(struct PrinterStatus), IPC_CREAT | 0640);
	if(shmid < 0){ perror("shmid"); exit(1); }

	ptrs = (struct PrinterStatus *)shmat(shmid, NULL, 0);
	if( ptrs == (void *)-1){
		perror("shmat");
		exit(1);
	}

	for(int i=0; i<PRINTERS; i++){
		ptrs->printers[i] = 0;
	}

	semid = semget(SHMKEY, 1, IPC_CREAT | 0640);
	if(semid < 0){ perror("semget"); exit(1); }
	semctl(semid, 0, SETVAL, PRINTERS);

	printf("Office with %d printers started\n", PRINTERS);

	for(int i=1; i<=USERS; i++){
		pid = fork();
		if(pid == 0){
			userprocess(semid, ptrs, i);
			exit(0);
		}
	}

	for(int i=1; i<=USERS; i++){
		wait(NULL);
	}

	shmdt((void *)ptrs);
	shmctl(shmid, IPC_RMID, NULL);
	semctl(semid, 0, IPC_RMID, 0);
	printf("All users finished printing\n");
	return 0;
}
