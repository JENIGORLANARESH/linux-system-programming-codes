#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *calc_fact(void *arg){
	for(int i=0; i<=10; i++){
		long fact = 1;
		for(int j=1; j<=i; j++){
			fact = fact * j;
		}
		printf("Factorial of %d = %ld\n", i, fact);
	}
	pthread_exit(NULL);
}

int main(void){
	pthread_t thread;
	pthread_create(&thread, NULL, calc_fact, NULL);
	pthread_join(thread, NULL);
	return 0;
}
