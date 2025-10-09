#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int a = 5, b= 4, Sum = 0;

pthread_mutex_t lock;

void *sum(void *arg){
	pthread_mutex_lock(&lock);
	Sum = a + b;
	printf("Sum = %d + %d = %d\n", a, b, Sum);
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main(void){
	pthread_t t1;

	if( pthread_mutex_init(&lock, NULL) != 0){
		perror("mutex init failed");
		return 1;
	}

	if( pthread_create(&t1, NULL, sum, NULL) != 0){
		perror("pthread_create failed");
		return 1;
	}

	pthread_join(t1, NULL);
	pthread_mutex_destroy(&lock);

	printf("Main : final sum = %d\n", Sum);
	return 0;
}
