#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#define LEN 10

void *string(void *arg){
	int len = *(int *)arg;
	char *result = malloc(sizeof(len+1));
	srand(time(NULL));	
	char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

	for(int i=0; i<=len; i++){
		int r = rand() % (sizeof(charset)+1);
		result[i] = charset[r];
	}

	result[len+1] = '\0';
	pthread_exit(result);
}

int main(void){
	pthread_t pid;
	void *str;
	int len = LEN;
	pthread_create(&pid, NULL, string, &len);
	pthread_join(pid, &str);
	printf("Random string : %s\n", (char *)str);
	free(str);
	return 0;
}
