#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct arr{
	int target;
	int n;
	int *array;
};

void *search(void *arg){
	struct arr *Arr= (struct arr *)arg;
	int n = Arr->n;
	int *array = Arr->array;
	int temp = Arr->target;
	for(int i=0; i<n; i++){
		if(temp == array[i]){
			printf("Number found at index : %d\n", i);
			pthread_exit(NULL);
		}
	}

	printf("Number not found\n");
	pthread_exit(NULL);
}

int main(void){
	pthread_t thread;
	struct arr array;
	int n;
	int target;

	printf("Enter no of elements : ");
	scanf("%d", &n);
	int Array[n];

	printf("Enter elements : \n");
	for(int i=0; i<n; i++){
		scanf("%d", &Array[i]);
	}

	printf("Enter target : ");
	scanf("%d", &target);

	array.n = n;
	array.array = Array;
	array.target = target;

	pthread_create(&thread, NULL, search, &array);
	pthread_join(thread, NULL);
	return 0;
}
