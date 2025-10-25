#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *even_odd(void *arg){
	int num = *(int *)arg;
	if(num % 2 == 0)
		printf("Even\n");
	else
		printf("Odd\n");
	pthread_exit(NULL);
}

int main(void){
	pthread_t thread;
	int num;
	printf("Enter num : ");
	scanf("%d", &num);

	pthread_create(&thread, NULL, even_odd, &num);
	pthread_join(thread, NULL);
	return 0;
}
