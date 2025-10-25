#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void *calc_sqrt(void *arg){
	double num = *(double *)arg;
	double result = sqrt(num);
	printf("square root of %.2f = %.2f\n", num, result);
	pthread_exit(NULL);
}

int main(void){
	pthread_t thread;
	double num;
	printf("Enter num : ");
	scanf("%lf", &num);
	
	if(pthread_create(&thread, NULL, calc_sqrt, &num) != 0){
		perror("failed to create thread");
		exit(1);
	}
	pthread_join(thread, NULL);

	return 0;
}
