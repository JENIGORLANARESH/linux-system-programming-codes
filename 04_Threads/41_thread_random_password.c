#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#define PASS_SIZE 10

void *generate_password(void *arg){
	char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789"
		"!@#$%^&*()_+";
	int size = strlen(charset);
	char password[PASS_SIZE+1];

	srand(time(NULL));

	for(int i=0; i<PASS_SIZE; i++){
		password[i] = charset[rand() % size];
	}
	password[PASS_SIZE] = '\0';
	printf("Random password : %s\n", password);
	pthread_exit(NULL);
}

int main(void){
	pthread_t thread;
	pthread_create(&thread, NULL, generate_password, NULL);
	pthread_join(thread, NULL);
	return 0;
}
