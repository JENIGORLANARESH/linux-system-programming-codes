#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define KEY 123
#define SIZE 100
#define PROCESSES 4

int main(void){
	int shmid;
	char *shmptr;
	shmid = shmget(KEY, SIZE, IPC_CREAT | 0666);
	if(shmid < 0){
		perror("shmget");
		exit(1);
	}
	shmptr = shmat(shmid, NULL, 0);
	if(shmptr == (char *)-1){
		perror("shmat");
		exit(1);
	}

	printf("Enter initial data into shared memory : ");
	fgets(shmptr, SIZE, stdin);
	shmptr[strcspn(shmptr, "\n")] = '\0';

	for(int i=0; i<PROCESSES; i++){
		int pid = fork();
		if(pid < 0){
			perror("fork");
			exit(1);
		}
		else if(pid == 0){
			int p_num = i+1;
			printf("Process %d : Data in shmptr : %s\n", p_num, shmptr);
			printf("Process %d : Enter data in shmptr : ", p_num);
			fgets(shmptr, SIZE, stdin);
			shmptr[strcspn(shmptr, "\n")] = '\0';
			printf("Process %d : wrote -> %s\n", p_num, shmptr);
			
			shmdt(shmptr);
			exit(0);
		}		
		else{
			wait(NULL);
		}
	}

	for(int i=0; i<PROCESSES; i++){
		wait(NULL);
	}

	printf("Final shared memeory content : %s\n", shmptr);

	shmdt(shmptr);
	shmctl(shmid, IPC_RMID, NULL);
	printf("shared memory deleted\n");
	return 0;
}
