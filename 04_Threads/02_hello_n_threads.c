#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *hello_thread(void *arg){
	int id = *(int *)arg;
	printf("Hello World from thread %d\n", id);
	return NULL;
}

int main(void){
	int n;
	printf("Enter number of threads : ");
	scanf("%d", &n);

	pthread_t threads_array[n];
	int threads_id[n];

	for(int i=0; i<n; i++){
		threads_id[i] = i+1;

		int ret = pthread_create(&threads_array[i], NULL, hello_thread, &threads_id[i]);
		if(ret != 0){
			perror("pthread_create is failed");
			return 1;
		}
	}

	for(int i=0; i<n; i++){
		int ret = pthread_join(threads_array[i], NULL);
		if(ret != 0){
			perror("pthread_join failed");
			return 1;
		}
	}

	return 0;
}
