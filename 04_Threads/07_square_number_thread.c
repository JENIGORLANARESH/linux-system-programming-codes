#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *square(void *arg){
	int n = *(int *)arg;
	int result = n * n;
	printf("Square of %d = %d\n", n , result);
	return NULL;
}

int main(void){
	int n;
	pthread_t t1;

	printf("Enter n : ");
	scanf("%d", &n);

	pthread_create(&t1, NULL, square, &n);

	pthread_join(t1, NULL);
	return 0;
}
