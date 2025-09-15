#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *numbers(void *arg){
	int id = *(int *)arg;
	for(int i=1; i<=10; i++){
		printf("Thread %d : %d\n", id, i);
		sleep(1);
	}
	return NULL;
}

int main(void){
	pthread_t t1, t2;
	int ret1, ret2;
	int id1 = 1, id2 = 2;

	ret1 = pthread_create(&t1, NULL, numbers, &id1);
	if(ret1 != 0){
		perror("pthread_create failed");
		return 1;
	}

	ret2 = pthread_create(&t2, NULL, numbers, &id2);
	if(ret2 != 0){
		perror("pthread_create failed");
		return 1;
	}

	ret1 = pthread_join(t1, NULL);
	ret2 = pthread_join(t2, NULL);

	if(ret1 != 0){
		perror("pthread_join failed");
		return 1;
	}
	if(ret2 != 0){
		perror("pthread_join failed");
		return 1;
	}

	return 0;
}
