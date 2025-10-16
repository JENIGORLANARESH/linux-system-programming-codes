#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define LIMIT 100

void *sum(void *arg){
	int *sum = malloc(sizeof(int));
	*sum = 0;
	for(int i=0; i<=100; i++){
		if(i%2 == 0){
			*sum = *sum + i;
		}
	}
	pthread_exit(sum);
}

int main(void){
	pthread_t thread;
	
	pthread_create(&thread, NULL, sum, NULL);

	void *result;
	pthread_join(thread, &result);
	printf("sum = %d\n", *(int *)result);
	return 0;
}
