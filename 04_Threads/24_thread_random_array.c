#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10
int arr[SIZE];

void *Thread(void *arg) {
	for(int i=0; i<SIZE; i++){
		arr[i] = rand() % 100;
	}
	return NULL;
}

int main() {
   	 pthread_t thread;

    	pthread_create(&thread, NULL, Thread, NULL);

    	pthread_join(thread, NULL);
		
	for(int i=0; i<SIZE; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
    	return 0;
}

