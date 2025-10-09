#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int shared_binary = 0;

sem_t bin_sem;

void* task(void* arg) {
    int id = *(int*)arg;

    printf("Task %d waiting for semaphore...\n", id);
    sem_wait(&bin_sem); 

    shared_binary += 1;
    printf("Task %d entered critical section, shared_binary=%d\n", id, shared_binary);
    sleep(1);

    sem_post(&bin_sem); 
    printf("Task %d exited critical section\n", id);

    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[3];

    sem_init(&bin_sem, 0, 1);

    for (int i = 0; i < 3; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, task, &ids[i]);
    }

    for (int i = 0; i < 3; i++)
        pthread_join(threads[i], NULL);

    sem_destroy(&bin_sem);

    return 0;
}

