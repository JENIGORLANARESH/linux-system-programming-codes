#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>


void *generate_num(void *arg){

	srand(time(NULL));
	int num = rand();
	printf("Random num = %d\n", num);
	pthread_exit(NULL);
}

int main(void){
	pthread_t thread;
	pthread_create(&thread, NULL, generate_num, NULL);
	pthread_join(thread, NULL);
	return 0;
}
