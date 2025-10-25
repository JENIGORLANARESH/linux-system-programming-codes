#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print(void *arg){
	int num = *(int *)arg;
	pthread_t tid = pthread_self();

	printf("received num : %d, Thread Id : %lu\n", num, tid);
	pthread_exit(NULL);
}

int main(void){
	pthread_t t1, t2;
	int n1;
	int n2;
	printf("Enter n1 , n2 : ");
	scanf("%d %d", &n1, &n2);
	pthread_create(&t1, NULL, print, &n1);
	pthread_create(&t2, NULL, print, &n2);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
