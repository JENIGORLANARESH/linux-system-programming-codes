#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t lock;

void *thread_id(void *arg){
	int num = *(int *)arg;
	pthread_mutex_lock(&lock);
	unsigned long id = (unsigned long)pthread_self();
	printf("Thread %d : ID = %lu\n", num, id);
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main(void){
	pthread_t t1, t2;
	int a=1,b=2;	
	if( pthread_mutex_init(&lock, NULL) != 0){
		perror("mutex init failed");
		return 1;
	}

	if( pthread_create(&t1, NULL, thread_id, &a) != 0){
		perror("pthread_create failed");
		return 1;
	}

	if( pthread_create(&t2, NULL, thread_id, &b) != 0){
		perror("pthread_create failed");
		return 1;
	}

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	

	pthread_mutex_destroy(&lock);
	return 0;
}
