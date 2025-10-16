#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct array{
	char **strings;
	int size;
};

void *sort(void *arg){
	struct array *a = (struct array *)arg;
	int size = a->size;
	for(int i=0; i<a->size-1; i++){
		for(int j=0; j<a->size-i-1; j++){
			if(strcmp(a->strings[j], a->strings[j+1]) > 0){
				char *temp = a->strings[j];
				a->strings[j] = a->strings[j+1];
				a->strings[j+1] = temp;
			}
		}
	}
	pthread_exit(NULL);
}

int main(void){
	pthread_t pid;
	struct array abc;
	printf("Enter size of array : ");
	scanf("%d", &abc.size);
	getchar();

	abc.strings = malloc(abc.size * sizeof(char *));
	
	printf("Enter stings : \n");
	for(int i=0; i<abc.size; i++){
		abc.strings[i] = malloc(100);
		scanf("%s", abc.strings[i]);
	}

	pthread_create(&pid, NULL, sort, &abc);
	pthread_join(pid, NULL);

	printf("Sorted array :\n");
	for(int i=0; i<abc.size; i++){
		printf("%s -> ", abc.strings[i]);
		free(abc.strings[i]);
	}
	free(abc.strings);
	printf("\n");
	return 0;
}
