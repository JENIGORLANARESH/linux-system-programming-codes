#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 1234
#define SEM_KEY 5678
#define SIZE 1024

int main(void){
	int semid, shmid;
	char *shmptr;

	shmid = shmget(SHM_KEY, SIZE, 0640);
	if(shmid < 0){
		perror("shmget");
		exit(1);
	}
	shmptr = shmat(shmid, NULL, 0);
	if(shmptr == (char *)-1){
		perror("shmat");
		exit(1);
	}

	semid = semget(SEM_KEY, 1, 0640);
	if(semid < 0){
		perror("semget");
		exit(1);
	}

	printf("Enter message : ");
	fgets(shmptr, SIZE, stdin);

	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_op = 1;
	sb.sem_flg = 0;

	semop(semid, &sb, 1);

	shmdt(shmptr);

	return 0;
}
