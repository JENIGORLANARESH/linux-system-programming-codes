#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* calculate_length(void* arg) {
        char* str = (char*)arg;
        int length = strlen(str);
        printf("The length of the string \"%s\" is: %d\n", str, length);
        pthread_exit(NULL);
}

int main() {
        pthread_t thread;
        char str[100];

        printf("Enter a string: ");
        scanf("%s", str); 

        if (pthread_create(&thread, NULL, calculate_length, (void*)str) != 0) {
                perror("Failed to create thread");
                return 1;
        }
        pthread_join(thread, NULL);
        return 0;
}

