#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void *square(void *arg){
	int num = *(int *)arg;
	int *perfect = malloc(sizeof(int));
	if(num < 0){
		*perfect = 0;
		pthread_exit(perfect);
	}
	int root = (int)sqrt(num);
	if(root * root == num){
		*perfect = 1;
		pthread_exit(perfect);
	}
	else{
		*perfect = 0;
		pthread_exit(perfect);
	}
}

int main(void){
	pthread_t pid;
	int num;
	printf("Enter num : ");
	scanf("%d", &num);
	pthread_create(&pid, NULL, square, &num);

	void *perfect;
	pthread_join(pid, &perfect);
	if(*(int *)perfect)
		printf("perfect square\n");
	else
		printf("not a perfect square\n");
	free(perfect);
	return 0;
}
