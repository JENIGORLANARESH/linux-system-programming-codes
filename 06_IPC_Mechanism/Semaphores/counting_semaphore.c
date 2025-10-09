#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_RESOURCES 2
#define NUM_TASKS 5

int shared_count = 0;

sem_t count_sem;

void* task(void* arg) {
    int id = *(int*)arg;

    printf("Task %d waiting for resource...\n", id);
    sem_wait(&count_sem);  

    shared_count += 1;
    printf("Task %d got resource, shared_count=%d\n", id, shared_count);
    sleep(1); 
    shared_count -= 1;

    sem_post(&count_sem); 
    printf("Task %d released resource\n", id);

    return NULL;
}

int main() {
    pthread_t threads[NUM_TASKS];
    int ids[NUM_TASKS];

    sem_init(&count_sem, 0, MAX_RESOURCES);

    for (int i = 0; i < NUM_TASKS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, task, &ids[i]);
    }

    for (int i = 0; i < NUM_TASKS; i++)
        pthread_join(threads[i], NULL);

    sem_destroy(&count_sem);

    return 0;
}

