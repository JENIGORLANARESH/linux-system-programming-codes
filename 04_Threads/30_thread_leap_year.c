#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *leap(void *arg){
	int year = *(int *)arg;
	int *is_Leap = malloc(sizeof(int));
	if( ((year%4 == 0) && (year%100 != 0)) || (year % 400 == 0)){
		*is_Leap = 1;
	}
	else{
		*is_Leap = 0;
	}
	pthread_exit(is_Leap);
}

int main(void){
	pthread_t pid;
	int year;
	printf("Enter year : ");
	scanf("%d", &year);
	pthread_create(&pid, NULL, leap, &year);
	
	void *Leap;
	pthread_join(pid, &Leap);
	if(*(int *)Leap)
		printf("Leap Year\n");
	else
		printf("Not a Leap year\n");
	free(Leap);
	return 0;
}
