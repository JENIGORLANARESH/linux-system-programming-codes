#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

void *palindrome(void *arg){
	char *str = (char *)arg;
	int end = strlen(str)-1, start = 0;
	while(start < end){
		if(str[start] != str[end]){
			printf("Not a Palindrome\n");
			return NULL;
		}
		start++;
		end--;
	}
	printf("Palindrome\n");
	return NULL;
}

int main(void){
	pthread_t t1;
	int ret;
	char str[1024];
	printf("Enter str : ");
	fgets(str, sizeof(str), stdin);
	str[strcspn(str, "\n")] = '\0';

	ret = pthread_create(&t1, NULL, palindrome, str);
	if(ret != 0){
		perror("pthread_create failed");
		return 1;
	}

	pthread_join(t1, NULL);

	return 0;
}
