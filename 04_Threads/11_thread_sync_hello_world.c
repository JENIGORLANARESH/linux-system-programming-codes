#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t lock;

void *hello_world(void *arg){
	pthread_mutex_lock(&lock);
	printf("Hello World\n");
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main(void){
	pthread_t t1, t2;
	
	if( pthread_mutex_init(&lock, NULL) != 0){
		perror("pthread_mutex_init failed");
		return 1;
	}

	if( (pthread_create(&t1, NULL, hello_world, NULL)) < 0){
		perror("pthread_create failed");
		return 1;
	}
	if( (pthread_create(&t2, NULL, hello_world, NULL)) < 0){
		perror("pthread_create failed");
		return 1;
	}

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&lock);

	return 0;
}
