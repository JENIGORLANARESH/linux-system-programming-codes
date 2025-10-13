#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define N 5

sem_t forks[N];

void *philosopher(void *arg){
	int id = *(int *)arg;
	int left = id;
	int right = (id+1)%N;
	while(1){
		printf("Philosopher %d thinking\n", id);
		sleep(rand()%3+1);
		printf("Philosopher %d is hungry\n", id);

		if(id % 2 == 0){
			sem_wait(&forks[right]);
			printf("Philosopher %d picks right fork %d\n", id, right);
			sem_wait(&forks[left]);
			printf("Philosopher %d picks left fork %d\n", id, left);
		}
		else{
			sem_wait(&forks[left]);
			printf("Philosopher %d picks left fork %d\n", id, left);
			sem_wait(&forks[right]);
			printf("Philosopher %d picks right fork %d\n", id, right);
		}
		printf("Philosopher %d is eating \n", id);
		sleep(rand()%2+1);
		printf("philosopher %d put down left %d and right %d\n", id, left , right);
		printf("Philosopher %d completed eating\n", id);
		sem_post(&forks[left]);
		sem_post(&forks[right]);
		sleep(rand()%2+1);
	}
	return NULL;
}

int main(void){
	pthread_t pids[N];	
	int ids[N];
	for(int i=0; i<N; i++){
		sem_init(&forks[i], 0, 1);
	}	

	for(int i=0; i<N; i++){
		ids[i] = i;
		pthread_create(&pids[i], NULL, philosopher, &ids[i]);
	}

	for(int i=0; i<N; i++){
		pthread_join(pids[i], NULL);
	}

	for(int i=0; i<N; i++){
		sem_destroy(&forks[i]);
	}

	return 0;
}

