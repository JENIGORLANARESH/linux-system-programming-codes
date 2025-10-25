#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_INPUT 100

void* read_input(void* arg) {
    char* input = (char*)arg;
    printf("Enter text: ");
    if (fgets(input, MAX_INPUT, stdin) != NULL) {
        size_t len = 0;
	while (input[len] != '\0') len++;
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        printf("You entered: %s\n", input);
    } else {
        printf("Error reading input.\n");
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    char input[MAX_INPUT];
    if (pthread_create(&thread, NULL, read_input, input) != 0) {
        perror("Failed to create thread");
        return 1;
    }
    pthread_join(thread, NULL);
    return 0;
}

