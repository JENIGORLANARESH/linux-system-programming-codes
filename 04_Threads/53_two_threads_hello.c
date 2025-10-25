#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* print_hello(void* arg) {
        pthread_t tid = pthread_self();
        printf("Hello World thread ID: %lu\n", tid);
        pthread_exit(NULL);
}

int main() {
        pthread_t thread1, thread2;

        if (pthread_create(&thread1, NULL, print_hello, NULL) != 0) {
                perror("create thread1");
                return 1;
        }

        if (pthread_create(&thread2, NULL, print_hello, NULL) != 0) {
                perror("Failed to create thread2");
                return 1;
        }

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        return 0;
}

