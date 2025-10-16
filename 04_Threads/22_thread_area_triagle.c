#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct triagle{
	int base;
	int height;
};

void *area_triagle(void *arg){
	struct triagle *tri = (struct triagle *)arg;
	float *area = malloc(sizeof(float));
	//int b = tri->base;
	//int h = tri->height;
	*area = (tri->base * tri->height)/2.0;
	pthread_exit(area);
}

int main(void){
	pthread_t thread;
	struct triagle t;
	printf("Enter base : ");
	scanf("%d", &t.base);
	printf("Enter height : ");
	scanf("%d", &t.height);

	pthread_create(&thread, NULL, area_triagle, &t);
	
	void *area;
	pthread_join(thread, &area);

	printf("Area : %.2f\n", *(float *)area);

	return 0;
}
