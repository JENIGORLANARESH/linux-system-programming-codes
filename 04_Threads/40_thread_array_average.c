#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct arr{
	int n;
	int *array;
};

void *avg(void *arg){
	struct arr *Arr= (struct arr *)arg;
	int n = Arr->n;
	int *array = Arr->array;

	int sum = 0;
	for(int i=0; i<n; i++){
		sum = sum + array[i];
	}

	double avrg = (double)sum / n;
	printf("Average : %.2f\n", avrg);
	pthread_exit(NULL);
}

int main(void){
	pthread_t thread;
	struct arr array;
	int n;
	
	printf("Enter no of elements : ");
	scanf("%d", &n);
	int Array[n];

	printf("Enter elements : \n");
	for(int i=0; i<n; i++){
		scanf("%d", &Array[i]);
	}

	array.n = n;
	array.array = Array;

	pthread_create(&thread, NULL, avg, &array);
	pthread_join(thread, NULL);
	return 0;
}
