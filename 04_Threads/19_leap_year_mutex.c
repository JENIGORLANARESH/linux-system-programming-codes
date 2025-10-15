#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;

int isLeap(int year){
	if((year % 4 == 0) && (year % 100 != 0))
		return 1;
	if(year % 400 == 0)
		return 1;
	return 0;
}

void *leap(void *arg){
	int year = *(int *)arg;
	pthread_mutex_lock(&mutex);
	if(isLeap(year)){
		printf("Leap\n");
	}
	else
		printf("Not Leap\n");
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(void){
	int year;
	printf("Enter year : ");
	scanf("%d", &year);
	pthread_t thread;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread, NULL, leap, &year);

	pthread_join(thread, NULL);
	pthread_mutex_destroy(&mutex);
	return 0;
}
