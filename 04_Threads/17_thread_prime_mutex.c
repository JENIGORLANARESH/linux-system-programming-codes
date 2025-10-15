#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

pthread_mutex_t mutex;

int isPrime(int n){
	if(n <= 1)
		return 0;
	if(n == 2)
		return 1;
	for(int i=2; i<=sqrt(n); i++){
		if(n % i == 0){
			return 0;
		}
	}
	return 1;
}

void *prime(void *arg){
	int limit = *(int *)arg;
	for(int i=0; i<limit; i++){
		if(isPrime(i)){
			pthread_mutex_lock(&mutex);
			printf("Prime : %d\n", i);
			pthread_mutex_unlock(&mutex);
		}
		usleep(100000);
	}
	return NULL;
}

int main(void){
	pthread_t thread;
	int limit;
	printf("Enter limit : ");
	scanf("%d", &limit);

	pthread_mutex_init(&mutex, NULL);

	pthread_create(&thread, NULL, prime, &limit);

	pthread_join(thread, NULL);

	pthread_mutex_destroy(&mutex);

	return 0;
}
