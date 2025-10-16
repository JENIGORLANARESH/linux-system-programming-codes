#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *Thread(void *arg) {
    long *sum = malloc(sizeof(long));
    *sum = 0;
    for (int i = 1; i <= 100; i++) {
        *sum = *sum + (i * i);
    }
    pthread_exit(sum);  
}

int main() {
    pthread_t thread;
    void *result;

    pthread_create(&thread, NULL, Thread, NULL);

    pthread_join(thread, &result);

    printf("Sum of squares from 1 to 100 = %ld\n", *(long *)result);

    free(result);
    return 0;
}

