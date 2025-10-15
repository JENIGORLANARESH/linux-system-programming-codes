#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define SIZE 1024
char buffer[SIZE];
pthread_mutex_t mutex;

void *Message(void *arg){
	char message[SIZE];
	while(1){
		int id = *(int *)arg;
		pthread_mutex_lock(&mutex);
		printf("Thread: %d, Enter message : ", id);
		fgets(message, SIZE, stdin);
		message[strcspn(message, "\n")] = '\0';
		strcpy(buffer, message);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	return NULL;
}

int main(void){
	pthread_t thread;
	pthread_mutex_init(&mutex, NULL);
	int id = 1;
		pthread_create(&thread, NULL, Message, &id);

	while(1){
		sleep(2);
		pthread_mutex_lock(&mutex);
		if(strlen(buffer) > 0){
			printf("Main thread : buffer : %s\n", buffer);
		}
		pthread_mutex_unlock(&mutex);
		if(strcmp(buffer, "exit") == 0){
			break;
		}
	}

	pthread_join(thread, NULL);
	pthread_mutex_destroy(&mutex);

	return 0;
}
