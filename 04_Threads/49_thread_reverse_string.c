#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* reverse_string(void* arg) {
    	char* str = (char*)arg;
    	int len = strlen(str);
    	printf("Original String: %s\n", str);
    	for (int i = 0; i < len / 2; i++) {
        	char temp = str[i];
        	str[i] = str[len - i - 1];
        	str[len - i - 1] = temp;
    	}
    	printf("Reversed String: %s\n", str);
    	pthread_exit(NULL);
}

int main() {
    	pthread_t thread;
    	char str[100];
    	printf("Enter a string: ");
    	scanf("%s", str); 
    	if (pthread_create(&thread, NULL, reverse_string, (void*)str) != 0) {
        	perror("create thread");
        	return 1;
    	}
    	pthread_join(thread, NULL);
    	return 0;
}

