#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
long long sum;

void *fibsum(void *arg){
	int limit = *(int *)arg;
	long long *fib = malloc(sizeof(long long)*(limit+1));
	fib[0] = 0;
	long long localsum = 0;
	if(limit >= 1){
		fib[1] = 1;
		localsum = 1;
	}

	for(int i=2; i<limit; i++){
		fib[i] = fib[i-1] + fib[i-2];
		localsum = localsum + fib[i];
	}

	pthread_mutex_lock(&mutex);
	sum = localsum;
	pthread_mutex_unlock(&mutex);

	free(fib);

	return NULL;
}

int main(void){
	int limit;
	printf("Enter limit : ");
	scanf("%d", &limit);
	pthread_t thread;
	
	pthread_mutex_init(&mutex, NULL);
	
	pthread_create(&thread, NULL, fibsum, &limit);

	pthread_join(thread, NULL);

	printf("Sum of fibonacci upto limit : %d = %lld\n", limit, sum);

	pthread_mutex_destroy(&mutex);
	return 0;
}
