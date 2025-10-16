#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *fact(void *arg){
	int num = *(int *)arg;
	int *facto = malloc(sizeof(int));
	*facto = 1;
	for(int i=1; i<=num; i++){
		*facto = *facto * i;
	}
	pthread_exit(facto);
}

int main(void){
	pthread_t pid;
	int n;
	printf("Enter num : ");
	scanf("%d", &n);

	pthread_create(&pid, NULL, fact, &n);
	
	void *val;

	pthread_join(pid, &val);
	printf("FAct of %d is : %d\n", n, *(int *)val);
	free(val);
	return 0;
}
