#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void *timedate(void *arg){
	time_t now = time(NULL);
	//struct tm *t = localtime(&now);
	printf("Current time = %s", ctime(&now));
	return NULL;
}

int main(void){
	pthread_t t1;
	pthread_create(&t1, NULL, timedate, NULL);
	pthread_join(t1, NULL);
	return 0;
}
