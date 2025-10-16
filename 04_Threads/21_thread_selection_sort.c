#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int arr[] = {4, 2, 6, 2, 0, 1, 8};

void *selection_sort(void *arg){
	for(int i=0; i<6; i++){
		int min_index = i;
		for(int j=i+1; j<7; j++){
			if(arr[min_index] > arr[j]){
				min_index = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[min_index];
		arr[min_index] = temp;
	}
	return NULL;
}

int main(void){
	pthread_t thread;
	pthread_create(&thread, NULL, selection_sort, NULL);

	pthread_join(thread, NULL);

	printf("After selection sort : \n");
	for(int i=0; i<7; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
