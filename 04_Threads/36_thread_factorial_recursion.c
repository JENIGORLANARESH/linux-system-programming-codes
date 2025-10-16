#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *factorial(void *arg){
	int num = *(int *)arg;
	int *result = malloc(sizeof(int));
	if(num == 0 || num == 1){
		*result = 1;
	}
	else{
		int minus = num-1;
		pthread_t pid;
		void *sub_result;
		pthread_create(&pid, NULL, factorial, &minus);
		pthread_join(pid, &sub_result);
		*result = num * *(int *)sub_result;
		free(sub_result);
	}
	pthread_exit(result);
}

int main(void){
	int num;
	pthread_t pid;
	printf("Enter n : ");
	scanf("%d", &num);
	pthread_create(&pid, NULL, factorial, &num);

	void *result;
	pthread_join(pid, &result);
	printf("Factorial of %d = %d\n", num , *(int *)result);
	free(result);
	return 0;
}
