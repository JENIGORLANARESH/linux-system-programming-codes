#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

void semaphore_wait(int semid){
	struct sembuf op = {0, -1, 0};
	semop(semid, &op, 1);
}

void semaphore_signal(int semid){
	struct sembuf op = {0, 1, 0};
	semop(semid, &op, 1);
}

int main(void){
	int semid;
	key_t key;
	int noprocesses = 3;
	int ret;

	key = ftok(".", 'S');
	if(key == -1){
		perror("ftok");
		exit(1);
	}

	semid = semget(key, 1, IPC_CREAT | 0666);
	if(semid < 0){
		perror("shmget");
		exit(1);
	}
	
	union semun arg;
	arg.val = 1;
	ret = semctl(semid, 0, SETVAL, arg);
	if(ret == -1){
		perror("semctl");
		exit(1);
	}
	printf("Semphore initialized to 1\n");

	for(int i=0; i<noprocesses; i++){
		pid_t pid;
		pid = fork();
		if(pid < 0){
			perror("fork");
			exit(1);
		}
		else if(pid == 0){
//			for(int i=0; i<2; i++){
				semaphore_wait(semid);
				printf("Process : %d , pid:%d entered critical section\n", i, getpid());
				sleep(2);
				printf("Process : %d , pid:%d leaving critical section\n", i, getpid());
				semaphore_signal(semid);
//			}
			exit(0);
		}
	}

	for(int i=0; i<noprocesses; i++){
		wait(NULL);
	}

	semctl(semid, 0, IPC_RMID);

	printf("All processes finished\n");
	return 0;
}
