#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *average(void *arg){
	int start = 1;
	int end = 100;
	int sum = 0;
	for(; start <= end; start++){
		sum = sum + start;
	}
	float *ave = malloc(sizeof(float));
	*ave = sum  / (float)end;
	pthread_exit(ave);
}

int main(void){
	pthread_t pid;
	pthread_create(&pid, NULL, average, NULL);
	void *aver;
	pthread_join(pid, &aver);
	printf("Average of sum from 1 to 100 : %.2f\n", *(float *)aver);
	free(aver);
	return 0;
}
