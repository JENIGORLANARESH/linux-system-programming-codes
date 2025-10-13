#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(void){
	int semid;
	int semkey;
	int no_sems;
	printf("Enter semkey : ");
        scanf("%d", &semkey);
	printf("Enter no of sems in a set : ");
	scanf("%d", &no_sems);
	
	semid = semget(semkey, no_sems, IPC_CREAT | 0666);
	if(semid < 0){
		perror("semget");
		exit(1);
	}

	printf("Semaphore set created successfully.\n");
	printf("semid : %d, semkey : %d, no of sems : %d\n", semid, semkey, no_sems);

	semctl(semid, 0, IPC_RMID);

	return 0;
}
