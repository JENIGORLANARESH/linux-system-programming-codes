#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>
#include <unistd.h>

#define SEMKEY 123

int counter = 0;
int semid;

struct sembuf wait = {0, -1, 0};
struct sembuf signal = {0, 1, 0};

void *incr(void *arg){
	int id = *(int *)arg;
	semop(semid, &wait, 1);
	for(int i=0; i<3; i++){
		int temp = counter;
		temp++;
		counter = temp;
		printf("Thread : %d , counter = %d\n", id, counter);
	}
	sleep(1);
	semop(semid, &signal, 1);
	return NULL;
}

int main(void){
	pthread_t pid[3];
	
	semid = semget(SEMKEY, 1, IPC_CREAT | 0666);
	semctl(semid, 0, SETVAL, 1);

	int ids[3] = {1,2,3};
	for(int i=0; i<3; i++){
		pthread_create(&pid[i], NULL, incr, &ids[i] );
	}

	for(int i=0; i<3; i++){
		pthread_join(pid[i], NULL);
	}

	printf("final counter = %d\n", counter);
	semctl(semid, 0, IPC_RMID);

	return 0;
}
