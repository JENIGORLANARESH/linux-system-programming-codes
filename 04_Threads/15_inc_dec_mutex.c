#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int var = 0;

pthread_mutex_t lock;

void *inc(void *arg){
	for(int i=0; i<5; i++){
		pthread_mutex_lock(&lock);
		var++;
		printf("Thread: INC > var = %d\n", var);
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
	return NULL;
}

void *dec(void *arg){
	for(int i=0; i<5; i++){
		pthread_mutex_lock(&lock);
		var--;
		printf("Thread: DEC > var = %d\n", var);
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
	return NULL;
}

int main(void){
	pthread_t t1, t2;

	if( pthread_mutex_init(&lock, NULL) != 0){
		perror("mutex init failed");
		return 1;
	}

	if( pthread_create(&t1, NULL, inc, NULL) != 0){
		perror("pthread_create failed");
		return 1;
	}
	if( pthread_create(&t2, NULL, dec, NULL) != 0){
		perror("pthread_create failed");
		return 1;
	}

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&lock);

	return 0;
}
