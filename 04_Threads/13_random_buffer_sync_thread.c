#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int n = 10;
int buffer[10];
int count = 0;

pthread_mutex_t lock;

void *generate_random(void *arg){
	int id = *(int *)arg;
	for(int i=0; i<n; i++){
		pthread_mutex_lock(&lock);
		int num = rand() % 100;
		if(count < n){
			buffer[count] = num;
			printf("Thread %d : %d stored at buffer[%d]\n", id, num, count);
			count++;
		}
		else{
			printf("Thread %d : %d not stored, buffer full\n", id, num);
		}
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
	return NULL;
}

int main(void){
	pthread_t t1, t2;
	int a=1,b=2;

	if( pthread_mutex_init(&lock, NULL) != 0){
		perror("mutex init failed");
		return 1;
	}

	if( pthread_create(&t1, NULL, generate_random, &a) != 0){
		perror("pthread_create failed");
		return 1;
	}
	if( pthread_create(&t2, NULL, generate_random, &b) != 0){
		perror("pthread_create failed");
		return 1;
	}

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&lock);
	printf("Buffer : ");
	for(int i=0; i<10; i++){
		printf("%d ", buffer[i]);
	}
	printf("\n");
	return 0;
}
