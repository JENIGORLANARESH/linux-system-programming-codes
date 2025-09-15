#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *hello(void *arg){
	printf("%s\n", (char *)arg);
	printf("Hello World\n");
	return NULL;
}

int main(void){
	pthread_t t1;
	
	int temp = pthread_create(&t1, NULL, hello, "Hello World");

	if(temp != 0){
		perror("pthread_create failed");
		return 1;
	}


	int ret = pthread_join(t1, NULL);

	if(ret != 0){
		perror("pthread_join failed");
		return 1;
	}

	return 0;
}
