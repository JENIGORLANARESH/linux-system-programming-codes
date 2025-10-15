#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define size 100
pthread_mutex_t mutex;
char string[size];
int isPalindrome = 1;

void *palindrome(void *arg){
	int j = strlen(string) - 1;
	int i = 0;
	while(i < j){
		if(string[i] != string[j]){
			pthread_mutex_lock(&mutex);
			isPalindrome = 0;
			pthread_mutex_unlock(&mutex);
		}
		i++;
		j--;
	}
	if(isPalindrome)
		printf("Palindrome\n");
	else
		printf("Not a Palindrome\n");
	return NULL;
}

int main(void){
	printf("Enter string : ");
	scanf("%s", string);
	pthread_t thread;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread, NULL, palindrome, NULL);

	pthread_join(thread, NULL);
	pthread_mutex_destroy(&mutex);
	return 0;
}
