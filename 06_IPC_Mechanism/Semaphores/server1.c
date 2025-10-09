#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 1234
#define SEM_KEY 5678
#define SIZE 1024
//server
int main(void){
	int semid, shmid;
	char *shmptr;
	shmid = shmget(SHM_KEY, SIZE, IPC_CREAT | 0640);
	if(shmid < 0){
		perror("shmget");
		exit(1);
	}
	shmptr = shmat(shmid, NULL, 0);
	if(shmptr == (char *)-1){
		perror("shmat");
		exit(1);
	}

	semid = semget(SEM_KEY, 1, IPC_CREAT | 0640);
	if(semid < 0){
		perror("shmget");
		exit(1);
	}
	semctl(semid, 0, SETVAL, 0);

	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_op = -1;
	sb.sem_flg = 0;

	printf("Server waiting for client...\n");
	semop(semid, &sb, 1);	// blocking state
	
	printf("Client > %s\n", shmptr);

	shmdt(shmptr);
	shmctl(shmid, IPC_RMID, NULL);
	semctl(semid, 0, IPC_RMID);

	return 0;
}
