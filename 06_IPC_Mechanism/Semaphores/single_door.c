#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

int door = 0;

sem_t bin_sem;

void *task(void *arg){
	unsigned int id = *(int *)arg;
	if(door == 1){
		printf(" %u Waiting\n", id);
	}
	sem_wait(&bin_sem);
	door++;
	printf("%u Entered\n", id);
	door--;
	printf("%u Exited \n", id);
	sem_post(&bin_sem);
	return NULL;
}

int main(void){
	pthread_t thread[3];
	int id[3];
	sem_init(&bin_sem, 0, 1);
	int num = 1;
	for(int i=0; i<3; i++){
		id[i] = i+1;
		pthread_create(&thread[i], NULL, task, &id[i]);
		num = num+1;
	}

	for(int i=0; i<3; i++){
		pthread_join(thread[i],NULL );
	}

	return 0;
}
