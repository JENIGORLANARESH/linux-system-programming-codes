#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int counter = 0;
#define loop 10000

pthread_spinlock_t spinlock;

void *incr(void *arg){
	for(int i=0; i<loop; i++){
		pthread_spin_lock(&spinlock);
		counter++;
		pthread_spin_unlock(&spinlock);
	}
	return NULL;
}

int main(void){

	pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);

	pthread_t threads[5];
	for(int i=0; i<5; i++){
		pthread_create(&threads[i], NULL, incr, NULL);
	}
	for(int i=0; i<5; i++){
		pthread_join(threads[i], NULL);
	}
	printf("Final counter = %d\n", counter);
	pthread_spin_destroy(&spinlock);
	return 0;
}
