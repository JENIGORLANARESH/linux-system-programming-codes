#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10
int arr[SIZE] = {55,32, 55, 22, 2,2, 4,88, 22, 99};

void *Thread(void *arg) {

        for(int i=0; i<SIZE-1; i++){
                for(int j=0; j< SIZE-i-1; j++){
                        if(arr[j] > arr[j+1]){
                                int temp = arr[j];
                                arr[j] = arr[j+1];
                                arr[j+1] = temp;
                        }
                }
        }

        return NULL;
}

int main() {
         pthread_t thread;

        pthread_create(&thread, NULL, Thread, NULL);

        pthread_join(thread, NULL);

        for(int i=0; i<SIZE; i++){
                printf("%d ", arr[i]);
        }
        printf("\n");
        return 0;
}

