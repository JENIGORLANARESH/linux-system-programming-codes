#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void *fib_sum(void *arg){
	int limit = *(int *)arg;
	int a = 0;
	int b = 1;
	int next;
	long long *sum = malloc(sizeof(long long));

	*sum = a + b;

	for(int i=2; i<=limit; i++){
		int next = a + b;
		*sum = *sum + next;
		a = b;
		b = next;
	}
	pthread_exit(sum);
}

int main(void){
	pthread_t thread;
	
	int limit;
	printf("Enter limit : ");
	scanf("%d", &limit);

	pthread_create(&thread, NULL, fib_sum, &limit);

	void *sum;

	pthread_join(thread, &sum);

	printf("sum of fib = %d\n", *(int *)sum);
	free(sum);

	return 0;
}
