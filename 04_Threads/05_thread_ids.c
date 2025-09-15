#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_id(void *arg){
	pthread_t ti;
	ti = pthread_self();

	unsigned long tid = (unsigned long)ti;
	printf("Hello from thread ID = %lu\n", tid);
	return NULL;
}

int main(void){
	pthread_t t1, t2;
	pthread_create(&t1, NULL, thread_id, NULL);
	pthread_create(&t2, NULL, thread_id, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}
