#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define size 6

void *max(void *arg){
	int *array = (int *)arg;
	int *maximum = malloc(sizeof(int));
	*maximum = array[0];
	for(int i=1; i<size; i++){
		if(*maximum < array[i])
			*maximum = array[i];
	}
	pthread_exit(maximum);
}

int main(void){
	pthread_t pid;
	int arr[size];
	printf("Enter leements : ");
	for(int i=0; i<size; i++){
		scanf("%d", &arr[i]);
	}
	pthread_create(&pid, NULL, max, arr);

	void *result;
	pthread_join(pid, &result);
	printf("Max : %d\n", *(int *)result);
	free(result);
	return 0;
}
