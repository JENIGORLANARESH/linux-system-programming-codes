#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *sum(void *arg){
	int num = *(int *)arg;
	int *result = malloc(sizeof(int));
	while(num > 0){
		int digit = num % 10;
		num = num / 10;
		*result = *result + digit;
	}
	pthread_exit(result);
}

int main(void){
	pthread_t pid;
	int num;
	printf("Enter n : ");
	scanf("%d", &num);
	pthread_create(&pid, NULL, sum, &num);

	void *result;
	pthread_join(pid, &result);
	printf("Sum of digits = %d\n", *(int *)result);
	free(result);
	return 0;
}
