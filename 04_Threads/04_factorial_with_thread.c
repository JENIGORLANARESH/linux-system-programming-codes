#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *factorial(void *arg){
	int n = *(int *)arg;
	unsigned long long result = 1;
	for(int i=1; i<=n; i++){
		result = result * i;
	}
	printf("Factorial of %d = %llu\n", n, result);
	return NULL;
}

int main(void){
	pthread_t t;
	int n;
	printf("Enter n : ");
	scanf("%d", &n);

	int ret = pthread_create(&t, NULL, factorial, &n);
	if(ret != 0){
		printf("pthread_create failed");
		return 1;
	}

	pthread_join(t, NULL);

	return 0;
}
